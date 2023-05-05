#include "Mainwindow.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedMemory mem("TimingShutdown");
    if (!mem.create(1))
    {
        QMessageBox::information(NULL, "提示", "程序已经在运行！");
        return 0;
    }
    MainWindow w;
    w.setWindowTitle("定时关机");
    w.show();
    w.hide();
    return a.exec();
}
