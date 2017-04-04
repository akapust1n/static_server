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
    void enqueueTask(Runnable* task);
    int activeThreadCount() const;

    bool tooManyThreadsActive() const;

    void startThread(Runnable* runnable = 0);
    void setMaxThreadCount(int count);

    mutable QMutex mutex;
    QSet<ThreadPoolThread*> allThreads;
    QQueue<ThreadPoolThread*> waitingThreads;
    QVector<Runnable*> queue;
    QWaitCondition noActiveThreads;

    int maxThreadCount;
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
    void setMaxThreadCount(int count);

private:
    ThreadPool(){};
    int maxThreads = 4; //default value
};

#endif // THREADPOOL_H
