#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QHBoxLayout>
#include "windows.h"
#include <qmenu.h>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QActionEvent>

#include "ThisRunTime.h"

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
    void Shutdown();
    void setThisRunTime(int thisRunTime);
    void setStatusBarMeg();

private slots:

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_automaticStartBox_clicked();

    void on_dateBox_clicked();

    void on_dateEdit_editingFinished();

    void on_timeEdit_editingFinished();

    void on_ButtonClose_clicked();

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
    int _thisRunTime = 0;
    bool shutDownSwich = false;
    QWidget *labelWidget = nullptr;
    QHBoxLayout *labelLayout = nullptr;
    QLabel* labelText = nullptr;

protected:
    /* 样式文件名称 */
    QString m_styleName;

private:
    /* 重写关闭按钮事件 */
    void closeEvent(QCloseEvent * event);
    void loadStyleSheet(const QString &sheetName);

    /* 鼠标事件：拖动窗口 */
private:
    QPoint lastPos;
    void mousePressEvent(QMouseEvent *event) {
        lastPos = event->globalPos();
    }

    void mouseMoveEvent(QMouseEvent *event) {
        if (this->isFullScreen()){
            return;
        }
        int dx = event->globalX() - lastPos.x();
        int dy = event->globalY() - lastPos.y();
        QPoint newPos = this->pos() + QPoint(dx, dy);
        this->move(newPos);
        lastPos = event->globalPos();
    }
};
#endif // MAINWINDOW_H
