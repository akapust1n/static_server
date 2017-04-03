#include "myserver.h"
#include <QScopedPointer>
#include <iostream>

MyServer::MyServer(int maxThreads, QString _rootDir, QObject* parent)
    : QTcpServer(parent)
    , rootDir(_rootDir)
{
    ThreadPool::getInstanse().setMaxThreadCount(maxThreads);
}

void MyServer::startServer()
{
    if (listen(QHostAddress::Any, 80)) {
        std::cout << "Server: started";
    } else {
        std::cout  << "Server: not started!";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "incoming Connection";
    MyTask* mytask = new MyTask(socketDescriptor, rootDir, this);
    mytask->setAutoDelete(true);
    ThreadPool::getInstanse().start(mytask);
}
