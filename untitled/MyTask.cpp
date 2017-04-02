#include "MyTask.h"
#include <QDebug>

#include "MyTask.h"
#include <QDebug>




MyTask::MyTask(qintptr socketDescriptor): m_socketDescriptor(socketDescriptor)
{

}

MyTask::~MyTask()
{
    qDebug() << "MyTask() destoroyed";
}

void MyTask::connected()
{

}

void MyTask::disconnected()
{

}
void MyTask::readyRead()
{
    QByteArray Buffer;
    Buffer.append("\r\nTask result = ");
    Buffer.append(QString::number(48));

   m_socket->write(Buffer);
   m_socket->close();
}

void MyTask::run()
{


    m_socket = new QTcpSocket();

    //     qDebug() << "A new socket created!";

  //  connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    //connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    m_socket->setSocketDescriptor(m_socketDescriptor);

    qDebug() << " Client connected at " << m_socketDescriptor;
//    for(int i = 0; i < 100; i++)
//    {
//        iNumber += 1;
//    }

   // qDebug() << "Task done";
   // m_socket->waitForReadyRead(m_timeout);
    QByteArray Buffer;
    Buffer.append("\r\nTask result = ");
    Buffer.append(QString::number(48));

   m_socket->write(Buffer);
   m_socket->disconnectFromHost();
    m_socket->waitForDisconnected();
   m_socket->close();


    qDebug() << "Socker closed";
}
