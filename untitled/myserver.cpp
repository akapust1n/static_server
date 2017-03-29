#include "myserver.h"
#include "MyClient.h"
#include <QScopedPointer>

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyServer::startServer()
{
    if(listen(QHostAddress::Any, 1234))
    {
       //  qDebug() << "Server: started";
    }
    else
    {
        // qDebug() << "Server: not started!";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    // At the incoming connection, make a client
    // and set the socket
   // QScopedPointer<MyClient> client(new  MyClient(this));
    // QScopedPointer<MyClient> client(new  MyClient(this));
    MyClient *client = new MyClient(this);
    client->setSocket(socketDescriptor);
}
