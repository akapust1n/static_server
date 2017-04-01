#include "MyTask.h"
#include <QDebug>

#include "MyTask.h"
#include <QDebug>


MyTask::MyTask()
{
     qDebug() << "MyTask()";
}

MyTask::~MyTask()
{
    qDebug() << "MyTask() destoroyed";
}

void MyTask::run()
{


    int iNumber = 0;
//    for(int i = 0; i < 100; i++)
//    {
//        iNumber += 1;
//    }

   // qDebug() << "Task done";
    emit Result(iNumber);
}
