#ifndef THISRUNTIME_H
#define THISRUNTIME_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "Mainwindow.h"

class ThisRunTime : public QObject
{
    Q_OBJECT
public:
    explicit ThisRunTime(QObject *parent = nullptr);
    void runTime();

private:
    int thisRunTime;

signals:
    void curNumber(int num);

public slots:


protected:

};

#endif // THISRUNTIME_H
