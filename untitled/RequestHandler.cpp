#include "RequestHandler.h"
#include <QDateTime>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>

RequestHandler::RequestHandler(QString _root_dir)
    : root_dir(_root_dir)
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
    if (method == "GET") {
        GET(url, protocol, socket);
    } else if (method == "HEAD") {
        HEAD(url, protocol, socket);
    } else if (method == "POST" || method == "PUT" || method == "PATCH" || method == "DELETE" || method == "TRACE" || method == "CONNECT" || method == "OPTIONS") {
        notAllowed(protocol, socket);
    } else {
        notImplemented(protocol, socket);
    }
    qDebug() << method << url << protocol;
}

QString RequestHandler::decodeUrl(const QString& _url)
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

void RequestHandler::GET(const QString url, const QString protocol, QTcpSocket* socket)
{
    qDebug() << "GET INTRO";
    QString path = root_dir + url;
    QString headers(getHeaders());
    int code;
    bool dir;
    if ((dir = isDirectory(path))) {
        if ((*path.end()) != '/')
            path += '/';
        qDebug() << "IT is Directory";
        path += "index.html";
    }
    qDebug() << "PATH" << path;
    if (fileExists(path)) {
        code = 200;
        QString extention = dir ? "html" : getExtension(url);
        headers += getContentHeaders(fileSize(path), extention);
        writeToSocket(getFullHeaders(protocol, getCode(code), headers), socket);
        QFile file(path);

        file.open(QIODevice::ReadOnly);
        writeToSocket(file.readAll(), socket);
        file.close();
    } else {
        qDebug() << "FILE NOT EXIST";
        code = (dir) ? 403 : 404;
        headers += getContentHeaders((QString((dir) ? forbidden : not_found).length()), "html");
        writeToSocket(getFullHeaders(protocol, getCode(code), headers), socket);
        writeToSocket((dir) ? forbidden : not_found, socket);
    }
}

void RequestHandler::HEAD(const QString& url, const QString& protocol, QTcpSocket* socket)
{
    QString path = root_dir + url;
    int code;
    bool dir;
    if ((dir = isDirectory(path))) {
        if ((*path.end()) != '/')
            path += '/';
        path += "index.html";
    }

    QString headers(getHeaders());

    if (fileExists(path)) {
        code = 200;
        QString extention = dir ? "html" : getExtension(url);
        headers += getContentHeaders(fileSize(path), extention);
        writeToSocket(getFullHeaders(protocol, getCode(code), headers), socket);
    } else {
        code = (dir) ? 403 : 404;
        headers += getContentHeaders((QString((dir) ? forbidden : not_found).length()), "html");
        writeToSocket(getFullHeaders(protocol, getCode(code), headers), socket);
        writeToSocket((dir) ? forbidden : not_found, socket);
    }
}

void RequestHandler::notAllowed(const QString& protocol, QTcpSocket* socket)
{
    const int code = 405;
    QString headers(getHeaders());
    headers += getContentHeaders(not_allowed.length(), "html");
    writeToSocket(getFullHeaders(protocol, getCode(code), headers), socket);
    writeToSocket(not_allowed, socket);
}

void RequestHandler::notImplemented(const QString& protocol, QTcpSocket* socket)
{
    const int code = 501;
    QString headers(getHeaders());
    headers += getContentHeaders(not_implemented.length(), "html");
    writeToSocket(getFullHeaders(protocol, getCode(code), headers), socket);
    writeToSocket(not_implemented, socket);
}

QString RequestHandler::getHeaders() const
{
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    QString date = locale.toString(QDateTime::currentDateTime(), "ddd, dd MMM yyyy hh:mm:ss 'GMT'");
    QString headers = QString("Server: WebServer/1.0 (Linux)\r\n") + QString("Date: ") + date + QString("\r\n")
        + QString("Connection: close\r\n");
    return headers;
}

bool RequestHandler::isDirectory(const QString& str) const
{
    struct stat s;
    return (stat(str.toStdString().c_str(), &s) == 0) && (s.st_mode & S_IFDIR);
}

bool RequestHandler::fileExists(const QString& path) const
{
    QFile file(path);
    return file.exists();
}

QString RequestHandler::getExtension(const QString& url) const
{
    int pos = url.lastIndexOf('.');
    qDebug()<<"EXTENTION"<<((pos != -1) ? url.split('.').last() : "txt");
    return (pos != -1) ? url.split('.').last() : "txt";
}

size_t RequestHandler::fileSize(const QString& path) const
{
    //ПЕРЕДЕЛАТЬ НА QSTRING? ВОЗМОЖНО QDATASTREAM
    std::ifstream in(path.toStdString(), std::ifstream::ate | std::ifstream::binary);
    return (size_t)in.tellg();
}

QString RequestHandler::getContentHeaders(size_t length, const QString& ext) const
{
    QString headers = QString("Content-Length: ") + QString::number(length) + QString("\r\n") + QString("Content-Type: ") + extToMime[ext] + QString("\r\n");
    return headers;
}

QString RequestHandler::getFullHeaders(const QString& protocol, const QString& code, const QString& headers) const
{
    QString response = protocol + QString(' ') + code + QString("\r\n") + headers + QString("\r\n");
    return response;
}

QString RequestHandler::getCode(int code) const
{
    switch (code) {
    case 200:
        return "200 OK";
    case 403:
        return "403 Forbidden";
    case 404:
        return "404 Not Found";
    case 405:
        return "405 Method Not Allowed";
    case 501:
        return "501 Not Implemented";
    default:
        return "200 OK"; //:)
    }
}

void RequestHandler::writeToSocket(const auto data, QTcpSocket* socket)
{
    QByteArray buffer;
    buffer.append(data);
    socket->write(buffer);
    socket->waitForBytesWritten(timeout);
}
