#ifndef MYTASK_H
#define MYTASK_H
#include <QTcpSocket>
#include <QObject>
#include <Runnable.h>

class MyTask : public QObject, public Runnable
{
    Q_OBJECT
public:
    MyTask(qintptr socketDescriptor, QObject *parent = 0);
    ~MyTask();

protected:
    void run();

private:
    QTcpSocket *m_socket;
    qintptr m_socketDescriptor;

};
#endif // MYTASK_H
