#include "myserver.h"
#include <QCommandLineParser>
#include <QCoreApplication>
#include <iostream>
#include <ThreadPool.h>



int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;

    QCommandLineOption cpuOption(QStringList() << "n"
                                               << "num-cores");
    parser.addOption(cpuOption);
    QCommandLineOption targetDirectoryOption(QStringList() << "r"
                                                           << "root-directory");
    parser.addOption(targetDirectoryOption);
    parser.process(a);

    const QStringList args = parser.positionalArguments();
    for (auto t : args) {
        std::cout << t.toStdString() << std::endl;
    }
    int maxTheads = parser.value("num-cores").toInt();
    QString rootDirectory = parser.value("root-directory");

    // Create an instance of a server and then start it.
    MyServer server(maxTheads, rootDirectory);
    server.startServer();

    return a.exec();
}
