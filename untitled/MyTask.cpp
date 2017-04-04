#include "MyTask.h"
#include "RequestHandler.h"
#include <QDebug>
#include <unistd.h>

MyTask::MyTask(qintptr socketDescriptor, QString _rootDir, QObject* parent)
    : QObject(parent)
    , m_socketDescriptor(socketDescriptor)
    , rootDir(_rootDir)
{
}

MyTask::~MyTask()
{
    //qDebug() << "MyTask() destoroyed";
}

void MyTask::run()
{
    RequestHandler requestHandler(rootDir);
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_socketDescriptor);

  //  qDebug() << " Client connected at " << m_socketDescriptor;

    requestHandler.handleRequest(m_socket);
    m_socket->close();

 //   qDebug() << "End run";
    delete m_socket;
}
