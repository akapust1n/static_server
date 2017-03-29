#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:

public slots:

};

#endif // MYSERVER_H
