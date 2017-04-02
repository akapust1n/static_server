#ifndef MYTASK_H
#define MYTASK_H
#include <QTcpSocket>
#include <QObject>
#include <Runnable.h>

class MyTask : public QObject, public Runnable
{
    Q_OBJECT
public:
    MyTask(qintptr socketDescriptor);
    ~MyTask();

signals:
    // notify to the main thread when we're done
    void Result(int Number);
public slots:
    void connected();
    void disconnected();
    void readyRead();

protected:
    void run();
private:
    QTcpSocket *m_socket;
    qintptr m_socketDescriptor;
    int m_timeout = 3000;

};
#endif // MYTASK_H
