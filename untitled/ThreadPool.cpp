#include "ThreadPool.h"
#include <QMutexLocker>
#include <QScopedPointer>

void ThreadPool::start(Runnable* Runnable)
{
    if (!Runnable)
        return;

    ThreadPoolPrivate* d = new ThreadPoolPrivate;
    QMutexLocker locker(&d->mutex);
    if (!d->tryStart(Runnable)) {
        d->enqueueTask(Runnable);

        if (!d->waitingThreads.isEmpty())
            d->waitingThreads.takeFirst()->runnableReady.wakeOne();
    }
}

ThreadPool& ThreadPool::getInstanse()
{

    static ThreadPool instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

ThreadPoolPrivate::ThreadPoolPrivate():isExiting(false),
        expiryTimeout(30000),
        maxThreadCount(qAbs(QThread::idealThreadCount())),
        reservedThreads(0),
        activeThreads(0)
{

}

bool ThreadPoolPrivate::tryStart(Runnable* task)
{
    if (allThreads.isEmpty()) {
        // always create at least one thread
        startThread(task);
        return true;
    }

    // can't do anything if we're over the limit
    if (activeThreadCount() >= maxThreadCount)
        return false;

    if (waitingThreads.count() > 0) {
        // recycle an available thread
        enqueueTask(task);
        waitingThreads.takeFirst()->runnableReady.wakeOne();
        return true;
    }

    if (!expiredThreads.isEmpty()) {
        // restart an expired thread
        ThreadPoolThread* thread = expiredThreads.dequeue();
        Q_ASSERT(thread->runnable == 0);

        ++activeThreads;

        if (task->autoDelete())
            ++task->ref;
        thread->runnable = task;
        thread->start();
        return true;
    }

    // start a new thread
    startThread(task);
    return true;
}

void ThreadPoolPrivate::enqueueTask(Runnable* runnable, int priority)
{
    if (runnable->autoDelete())
        ++runnable->ref;

    // put it on the queue
    QVector<QPair<Runnable*, int> >::const_iterator begin = queue.constBegin();
    QVector<QPair<Runnable*, int> >::const_iterator it = queue.constEnd();
   // if ((it != begin) && (priority > (*(it - 1)).second))
       // it = std::upper_bound(begin, --it, priority);
        queue.insert(it - begin, qMakePair(runnable, priority));
}

int ThreadPoolPrivate::activeThreadCount() const
{
    return (allThreads.count()
              - expiredThreads.count()
                - waitingThreads.count()
                + reservedThreads);

}

bool ThreadPoolPrivate::tooManyThreadsActive() const
{
    const int activeThreadCount = this->activeThreadCount();
    return activeThreadCount > maxThreadCount && (activeThreadCount - reservedThreads) > 1;

}

void ThreadPoolPrivate::startThread(Runnable *runnable)
{
    QScopedPointer <ThreadPoolThread> thread(new ThreadPoolThread(this));
            thread->setObjectName(QLatin1String("Thread (pooled)"));
            allThreads.insert(thread.data());
            ++activeThreads;

            if (runnable->autoDelete())
                ++runnable->ref;
            thread->runnable = runnable;
            thread.take()->start();

}

void ThreadPoolPrivate::setmaxThreadCount(int count)
{
    maxThreadCount = count;
}

ThreadPoolThread::ThreadPoolThread(ThreadPoolPrivate *manager): manager(manager), runnable(0)
{

}

void ThreadPoolThread::run()
{
    QMutexLocker locker(&manager->mutex);
        for(;;) {
            Runnable *r = runnable;
            runnable = 0;

            do {
                if (r) {
                    const bool autoDelete = r->autoDelete();


                    // run the task
                    locker.unlock();
    #ifndef QT_NO_EXCEPTIONS
                    try {
    #endif
                        r->run();
    #ifndef QT_NO_EXCEPTIONS
                    } catch (...) {
                        qWarning("Qt Concurrent has caught an exception thrown from a worker thread.\n"
                                 "This is not supported, exceptions thrown in worker threads must be\n"
                                 "caught before control returns to Qt Concurrent.");
                        registerThreadInactive();
                        throw;
                    }
    #endif
                    locker.relock();

                    if (autoDelete && !--r->ref)
                        delete r;
                }

                // if too many threads are active, expire this thread
                if (manager->tooManyThreadsActive())
                    break;

                r = !manager->queue.isEmpty() ? manager->queue.takeFirst().first : 0;
            } while (r != 0);

            if (manager->isExiting) {
                registerThreadInactive();
                break;
            }

            // if too many threads are active, expire this thread
            bool expired = manager->tooManyThreadsActive();
            if (!expired) {
                manager->waitingThreads.enqueue(this);
                registerThreadInactive();
                // wait for work, exiting after the expiry timeout is reached
              runnableReady.wait(locker.mutex(), manager->expiryTimeout);
                ++manager->activeThreads;
                if (manager->waitingThreads.removeOne(this))
                    expired = true;
            }
            if (expired) {
                manager->expiredThreads.enqueue(this);
                registerThreadInactive();
                break;
            }
        }
}

void ThreadPoolThread::registerThreadInactive()
{
    if (--manager->activeThreads == 0)
         manager->noActiveThreads.wakeAll();
}
