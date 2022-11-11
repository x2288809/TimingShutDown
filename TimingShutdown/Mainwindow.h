#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QDialog>
#include <QFile>
#include <QDomNodeList>
#include <QLabel>
#include "windows.h"
#include <qmenu.h>
#include <QMenu>
#include <QSystemTrayIcon>
#include "windows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void TimingShutdown(QString time);
    void TimingShutdown(QString date,QString time);
    void TimerEvent(QTimer* timer);
    /* 显示和隐藏 */
    void HideShowTiming(QLabel* label);

private slots:

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_automaticStartBox_clicked();

    void on_dateBox_clicked();

    void on_dateEdit_editingFinished();

    void on_timeEdit_editingFinished();

signals:


private:
    Ui::MainWindow *ui;

    QSystemTrayIcon* SysIcon;
    QAction *min; //最小化
//    QAction *max; //最大化
    QAction *restor; //恢复
    QAction *quit; //退出
    QMenu *menu;
    int automatic;
    int dateBoxArg;
    bool shutDownSwich = false;

private:
    /* 重写关闭按钮事件 */
    void closeEvent(QCloseEvent * event);
};
#endif // MAINWINDOW_H
