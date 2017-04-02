#include "MyTask.h"
#include <QDebug>
#include "RequestHandler.h"
#include <unistd.h>

MyTask::MyTask(qintptr socketDescriptor, QObject* parent)
    : QObject(parent)
    , m_socketDescriptor(socketDescriptor)
{
}

MyTask::~MyTask()
{
    qDebug() << "MyTask() destoroyed";
}

void MyTask::run()
{
    RequestHandler requestHandler;
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_socketDescriptor);

    qDebug() << " Client connected at " << m_socketDescriptor;
    m_socket->waitForReadyRead(3000);
    //qDebug()<< m_socket->readAll();
    //qDebug()<<"END READ ALL";
    requestHandler.handleRequest(m_socket);
    QByteArray Buffer;
    Buffer.append("\r\nTask result = ");

    Buffer.append(QString::number(48));

    m_socket->write(Buffer);
    m_socket->waitForBytesWritten(3000);
//usleep (3000* 1000);

    qDebug() << "End run";
    delete m_socket;
}


