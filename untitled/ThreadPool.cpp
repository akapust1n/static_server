#include "ThreadPool.h"
#include <QMutexLocker>
#include <QScopedPointer>
#include <qdebug.h>

void ThreadPool::start(Runnable* Runnable)
{
    if (!Runnable)
        return;

    static ThreadPoolPrivate* d = new ThreadPoolPrivate;
    d->setMaxThreadCount(maxThreads);
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

void ThreadPool::setMaxThreadCount(int count)
{
    maxThreads = count;
}

ThreadPoolPrivate::ThreadPoolPrivate()
    : isExiting(false)
    , maxThreadCount(qAbs(QThread::idealThreadCount()))
    , activeThreads(0)
{
}

bool ThreadPoolPrivate::tryStart(Runnable* task)
{
    if (allThreads.isEmpty()) {
        // always create at least one thread
        startThread(task);
        qDebug() << "Start new Thread p1";

        return true;
    }

    // can't do anything if we're over the limit
    if (activeThreadCount() >= maxThreadCount) {
        qDebug() << "Error thread limit";
        return false;
    }
    qDebug() << "Start new Thread p2";
    if (waitingThreads.count() > 0) {
        // recycle an available thread
        enqueueTask(task);
        waitingThreads.takeFirst()->runnableReady.wakeOne();
        return true;
    }

    qDebug() << "Start new Thread p3";
    // start a new thread
    startThread(task);
    return true;
}

void ThreadPoolPrivate::enqueueTask(Runnable* runnable)
{
    if (runnable->autoDelete())
        ++runnable->ref;

    // put it on the queue
    QVector<Runnable*>::const_iterator begin = queue.constBegin();
    QVector<Runnable*>::const_iterator it = queue.constEnd();

    queue.insert(it - begin, runnable);
}

int ThreadPoolPrivate::activeThreadCount() const
{
    qDebug() << "Active Threads" << (allThreads.count()
                                        - waitingThreads.count());
    qDebug() << "All Threads" << (allThreads.count());

    return (allThreads.count()
        - waitingThreads.count());
}

bool ThreadPoolPrivate::tooManyThreadsActive() const
{
    const int activeThreadCount = this->activeThreadCount();
    return activeThreadCount > maxThreadCount && (activeThreadCount) > 1;
}

void ThreadPoolPrivate::startThread(Runnable* runnable)
{
    QScopedPointer<ThreadPoolThread> thread(new ThreadPoolThread(this));
    thread->setObjectName(QLatin1String("Thread (pooled)"));
    allThreads.insert(thread.data());
    ++activeThreads;

    if (runnable->autoDelete())
        ++runnable->ref;
    thread->runnable = runnable;
    thread.take()->start();
}

void ThreadPoolPrivate::setMaxThreadCount(int count)
{
    maxThreadCount = count;
}

ThreadPoolThread::ThreadPoolThread(ThreadPoolPrivate* manager)
    : manager(manager)
    , runnable(0)
{
}

void ThreadPoolThread::run()
{
    QMutexLocker locker(&manager->mutex);
    for (;;) {
        Runnable* r = runnable;
        runnable = 0;

        do {
            if (r) {
                const bool autoDelete = r->autoDelete();

                // run the task
                locker.unlock();
                try {
                    r->run();
                } catch (...) {
                    qWarning("Error run task");
                    throw;
                }
                locker.relock();

                if (autoDelete && !--r->ref)
                    delete r;
            }

            //if too many threads are active, expire this thread
            if (manager->tooManyThreadsActive())
                break;

            r = !manager->queue.isEmpty() ? manager->queue.takeFirst() : 0;
        } while (r != 0);

        if (manager->isExiting) {
            registerThreadInactive();
            break;
        }

        //if too many threads are active, expire this thread
        bool expired = manager->tooManyThreadsActive();
        if (!expired) {
            manager->waitingThreads.enqueue(this);
            registerThreadInactive();
            // wait for work, exiting after the expiry timeout is reached # at now without timeout
            // runnableReady.wait(locker.mutex(), manager->expiryTimeout);
            runnableReady.wait(locker.mutex());

            ++manager->activeThreads;
            if (manager->waitingThreads.removeOne(this))
                expired = true;
        }
    }
}

void ThreadPoolThread::registerThreadInactive()
{
    if (--manager->activeThreads == 0)
        manager->noActiveThreads.wakeAll();
}
