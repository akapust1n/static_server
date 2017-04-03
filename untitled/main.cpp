#include "myserver.h"
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QString>
#include <ThreadPool.h>
#include <iostream>
#include <qdebug.h>
#include <unistd.h>

QString getProcs(int maxCores)
{
    switch (maxCores) {
    case 1:
        return "1";
    case 2:
        return "1,2";
    case 3:
        return "1,2,3";
    default:
        return "1,2,3,4";
    }
}

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

    int maxCores = 4;
    if (!args.isEmpty())
        if (!args.first().isEmpty())
            maxCores = args.first().toInt();
    int pid = getpid();

    QString rootDirectory = ".";
    if (!args.isEmpty())
        if (!args.last().isEmpty())
            rootDirectory = args.last();

    std::cout << " PID: " << pid;
    std::cout << " Cores: " << maxCores;

    QString tasknet = "sudo taskset -p -c " + getProcs(maxCores) + " " + QString::number(pid);
    system(tasknet.toStdString().c_str());

    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    std::cout << "availableProcessors: " << numCPU;

    // Create an instance of a server and then start it.
    int threadPoolSize = 1;
    MyServer server(threadPoolSize, rootDirectory);
    server.startServer();
    return a.exec();
}
