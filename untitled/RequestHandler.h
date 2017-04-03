#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include <QMap>
#include <QString>
#include <QTcpSocket>

class RequestHandler {
public:
    RequestHandler(QString _root_dir);
    void handleRequest(QTcpSocket* socket);

private:
    QString decodeUrl(const QString& _url);
    void GET(const QString url, const QString protocol, QTcpSocket* socket);
    void HEAD(const QString& url, const QString& protocol, QTcpSocket* socket);
    void notAllowed(const QString& protocol, QTcpSocket* socket);
    void notImplemented(const QString& protocol, QTcpSocket* socket);

    QString getHeaders() const;
    QString getContentHeaders(size_t length, const QString& ext) const;
    QString getFullHeaders(const QString& protocol, const QString& code,
        const QString& headers) const;

    bool isDirectory(const QString& str) const;
    bool fileExists(const QString& path) const;
    QString getExtension(const QString& url) const;
    size_t fileSize(const QString& path) const;
    QString getCode(int code) const;

    void writeToSocket(const auto data, QTcpSocket* socket);
    //void writeToSocket(const QByteArray data, QTcpSocket* socket);


    int timeout = 3000;

private:
    //consts
    const QString root_dir = ".";
    const QString not_found = "<html>"
                              "<head><title>Not Found</title></head>"
                              "<body><h1>404 Not Found</h1></body>"
                              "</html>";
    const QString forbidden = "<html>"
                              "<head><title>Forbidden</title></head>"
                              "<body><h1>403 Forbidden</h1></body>"
                              "</html>";
    const QString not_allowed = "<html>"
                                "<head><title>Not Allowed</title></head>"
                                "<body><h1>404 Method Not Allowed</h1></body>"
                                "</html>";
    const QString not_implemented = "<html>"
                                    "<head><title>Not Implemented</title></head>"
                                    "<body><h1>501 Not Implemented</h1></body>";
    QMap<QString, QString>
        extToMime = {
            { "txt", "text/plain" },
            { "html", "text/html" },
            { "css", "text/css" },
            { "js", "application/javascript" },
            { "jpg", "image/jpeg" },
            { "jpeg", "image/jpeg" },
            { "png", "image/png" },
            { "gif", "image/gif" },
            { "swf", "application/x-shockwave-flash" }
        };
};

#endif // REQUESTHANDLER_H
