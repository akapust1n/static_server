#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include <QTcpSocket>

class RequestHandler
{
public:
    RequestHandler();
    void handleRequest(QTcpSocket * socket);
private:
    QString decodeUrl(const QString _url);
};

#endif // REQUESTHANDLER_H
