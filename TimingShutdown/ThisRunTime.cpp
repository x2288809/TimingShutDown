#include "ThisRunTime.h"
#include <QDebug>

ThisRunTime::ThisRunTime(QObject *parent) : QObject(parent)
{

}

void ThisRunTime::runTime()
{
    qDebug() << "当前线程对象的地址: " << QThread::currentThread();
    int num = 0;
    while(1)
    {
        emit curNumber(num++);
        QThread::sleep(1);//单位：秒
    }
    qDebug() << "run() 执行完毕, 子线程退出...";
}

