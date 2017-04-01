#ifndef MYTASK_H
#define MYTASK_H
#include <QRunnable>

#include <QRunnable>
#include <QObject>
#include <Runnable.h>

class MyTask : public QObject, public Runnable
{
    Q_OBJECT
public:
    MyTask();
    ~MyTask();

signals:
    // notify to the main thread when we're done
    void Result(int Number);

protected:
    void run();
};
#endif // MYTASK_H
