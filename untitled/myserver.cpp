#include "myserver.h"
#include <QScopedPointer>

MyServer::MyServer(int maxThreads, QString rootDir, QObject* parent)
    : QTcpServer(parent)
{
    ThreadPool::getInstanse().setMaxThreadCount(maxThreads);
}

void MyServer::startServer()
{
    if (listen(QHostAddress::Any, 80)) {
        qDebug() << "Server: started";
    } else {
        qDebug() << "Server: not started!";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "incoming Connection";
    MyTask* mytask = new MyTask(socketDescriptor, this);
    mytask->setAutoDelete(true);
    ThreadPool::getInstanse().start(mytask);
}
