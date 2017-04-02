#include "RequestHandler.h"
#include <QTextCodec>
#include <QTextStream>
#include <sstream>
#include <string>

RequestHandler::RequestHandler()
{
}

void RequestHandler::handleRequest(QTcpSocket* socket)
{
    // qDebug()<<socket->readAll();
    //qDebug()<<"READ @";
    QByteArray buffer = socket->readAll();
    QString s = QString::fromUtf8(buffer);

    QTextStream stream(buffer);


    QString method, url, protocol = "HTTP/1.1";
    stream >> method >> url >> protocol;
    url = decodeUrl(url);
    // qDebug()<<temp;
    qDebug() << method << url << protocol;
    //qDebug() << this->serverAddress().toString() + ":" + QString::number(this->serverPort()) + " " + tokens[0] + " " + tokens[1];
}

QString RequestHandler::decodeUrl(const QString _url)
{
    const std::string url = _url.toStdString();
    std::string res;

    for (size_t i = 0; i < url.length(); ++i) {
        if (url[i] == '%') {
            int val;
            sscanf(url.substr(i + 1, 2).c_str(), "%x", &val);
            res += (char)val;
            i += 2;
        } else if (url[i] == '+') {
            res += ' ';
        } else {
            res += url[i];
        }
    }
    size_t pos;
    while ((pos = res.find("/../")) != std::string::npos) {
        res.erase(pos, 4);
    }
    if ((pos = res.find('?')) != std::string::npos) {
        res = res.substr(0, pos);
    }
    return QString::fromStdString(res);
}
