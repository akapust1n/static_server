#include "myserver.h"
#include "MyClient.h"
#include <QScopedPointer>

MyServer::MyServer(int maxThreads, QString rootDir, QObject* parent)
    : QTcpServer(parent)
{
}

void MyServer::startServer()
{
    if (listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server: started";
    } else {
        qDebug() << "Server: not started!";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{

  //  MyClient* client = new MyClient(this);
  //  client->setSocket(socketDescriptor);

    MyTask* mytask = new MyTask(socketDescriptor);
    mytask->setAutoDelete(true);
    ThreadPool::getInstanse().start(mytask);
}
