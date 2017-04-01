#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <QVector>

#include "Runnable.h"
#include <MyTask.h>
#include <QMutex>
#include <QObject>
#include <QPair>
#include <QQueue>
#include <QSet>
#include <QWaitCondition>
#include <qthread.h>

class ThreadPoolThread;
class ThreadPoolPrivate {

    friend class ThreadPoolThread;

public:
    ThreadPoolPrivate();

    bool tryStart(Runnable* task);
    void enqueueTask(Runnable* task, int priority = 0);
    int activeThreadCount() const;

//    void tryToStartMoreThreads();
   bool tooManyThreadsActive() const;

    void startThread(Runnable* runnable = 0);
//    void reset();
//    bool waitForDone(int msecs);
//    void clear();
//    bool stealRunnable(Runnable* runnable);
//    void stealAndRunRunnable(Runnable* runnable);
    void setmaxThreadCount(int count);

    mutable QMutex mutex;
    QSet<ThreadPoolThread*> allThreads;
    QQueue<ThreadPoolThread*> waitingThreads;
    QQueue<ThreadPoolThread*> expiredThreads;
    QVector<QPair<Runnable*, int> > queue;
    QWaitCondition noActiveThreads;

    bool isExiting;
    int expiryTimeout;
    int maxThreadCount = 5;
    int reservedThreads;
    int activeThreads;
};

class ThreadPoolThread : public QThread {
public:
    ThreadPoolThread(ThreadPoolPrivate* manager);
    void run() override;
    void registerThreadInactive();

    QWaitCondition runnableReady;
    ThreadPoolPrivate* manager;
    Runnable* runnable;
};

class ThreadPool : public QObject {
    Q_OBJECT

public:
    void start(Runnable* runnable);
    static ThreadPool &getInstanse();

private:
    ThreadPool(){};
    int maxThreads;
};

#endif // THREADPOOL_H
