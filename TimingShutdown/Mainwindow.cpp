#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QCloseEvent>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::Dialog);

    qDebug() << "主线程对象的地址: " << QThread::currentThread();

    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint); // 隐藏边框
    setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明

    labelWidget = new QWidget();
    labelLayout = new QHBoxLayout();

    loadStyleSheet("Mainwindow");

    /* 以下为系统托盘项 */
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化按钮
    menu = new QMenu(this);
    QIcon icon(":/icon.ico");
    SysIcon = new QSystemTrayIcon(this);
    SysIcon->setIcon(icon);
    this->setWindowIcon(icon);
    SysIcon->setToolTip("定时关机");
    min = new QAction("窗口最小化",this);
    connect(min,&QAction::triggered,this,&MainWindow::hide);
//    connect(min,SIGNAL(trigger()),this,&MainWindow::hide);
//    max = new QAction("窗口最大化",this);
//    connect(max,&QAction::triggered,this,&MainWindow::showMaximized);
    restor = new QAction("恢复窗口",this);
    connect(restor,&QAction::triggered,this,&MainWindow::showNormal);
    quit = new QAction("退出",this);
    //    connect(quit,&QAction::triggered,this,&MainWindow::close);
    connect(quit,&QAction::triggered,qApp,&QApplication::quit);
    connect(SysIcon,&QSystemTrayIcon::activated,this,&MainWindow::on_activatedSysTrayIcon);

    menu->addAction(min);
//    menu->addAction(max);
    menu->addAction(restor);
    menu->addSeparator(); //分割
    menu->addAction(quit);
    SysIcon->setContextMenu(menu);
    SysIcon->show();
//    close();

    // 创建定时器对象
    QTimer* timer = new QTimer(this);
    // 修改定时器对象的精度
    timer->setTimerType(Qt::PreciseTimer);

    labelText = new QLabel(this); //label内容，parent 或直接 parent
    labelText->setAlignment(Qt::AlignCenter);

    //    ConfigXML* config = new ConfigXML(this);

    /* 读取配置文件，初始化界面设置 */

    QSettings timingConfig("Config.ini", QSettings::IniFormat);
    timingConfig.beginGroup("TIMING");
    dateBoxArg = timingConfig.value("dateBoxArg").toInt();
    if(dateBoxArg == 1)
    {
        ui->dateBox->setChecked(true);
    }else if(dateBoxArg == 0){
        ui->dateBox->setChecked(false);
        ui->dateEdit->setEnabled(false);
    }

    automatic = timingConfig.value("automatic").toInt();
    if(automatic == 1)
    {
        ui->automaticStartBox->setChecked(true);
//        ui->startBtn->clicked();
        HideShowTiming(labelText);
        TimerEvent(timer);
    }else if(automatic == 0){
        ui->automaticStartBox->setChecked(false);
    }
    QString planDate = timingConfig.value("planDate").toString();
    QString planTime = timingConfig.value("planTime").toString();

    ui->dateEdit->setDate(timingConfig.value("planDate").toDate());
    ui->timeEdit->setTime(timingConfig.value("planTime").toTime());
    QString lastShutdownDate;
    lastShutdownDate.append("上次执行关机操作：");
    lastShutdownDate.append(timingConfig.value("lastDateShutDown").toString());
    ui->statusBar->showMessage(lastShutdownDate, 30000);//状态栏显示内容

    timingConfig.endGroup();

    qDebug() << "timeEdit：" <<ui->timeEdit->text();

    // 按钮 startBtn 的点击事件
    // 点击按钮启动或者关闭定时器, 定时器启动, 周期性得到当前时间
    connect(ui->startBtn, &QPushButton::clicked, this, [=]()
    {
        HideShowTiming(labelText);
        TimerEvent(timer);
    });

    connect(timer, &QTimer::timeout, this, [&]()
    {
        if(shutDownSwich == true)
        {
            labelText->setText("系统将于30秒后关机！");
            labelText->show();
            timer->stop();
            return;
        }
        QString dateText = ui->dateEdit->text();//设置的定时日期
        QString timingText = ui->timeEdit->text();//设置的定时时间
        if(dateBoxArg == 1)//设置了定时日期时
        {
//            qDebug() << "进来了：" << dateBoxArg;
            TimingShutdown(dateText, timingText);
        }
        if(dateBoxArg == 0)//未设置定时日期时
        {
//            qDebug() << "进来了：" << dateBoxArg;
            TimingShutdown(timingText);
        }
    });


    // 运行时间计时相关程序
    // 创建一个线程

    QThread* runTimeThr = new QThread;

    ThisRunTime *codeRunTime = new ThisRunTime;

    codeRunTime->moveToThread(runTimeThr);

    //线程启动后，立即执行runTime函数
    connect(runTimeThr, &QThread::started, codeRunTime, &ThisRunTime::runTime);

    //当curNumber信号发射出来时，执行如下方法
    connect(codeRunTime, &ThisRunTime::curNumber, this, [=](int num)
    {
        qDebug() << "计时：" << num;
        setThisRunTime(num);
        setStatusBarMeg();
    });

    runTimeThr->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* 定时关机函数 */
void MainWindow::TimingShutdown(QString time)
{
    QDate CurrentDate = QDate::currentDate();
    QTime CurrentTime = QTime::currentTime();
    QString CurrentDateText = CurrentDate.toString("yyyy-MM-dd");//当前日期
    QString CurrentTimeText = CurrentTime.toString("hh:mm");//当前时间
    if(time == CurrentTimeText)
    {
        Shutdown();
        time.end();
    }
}

void MainWindow::TimingShutdown(QString date, QString time)
{
    QDate CurrentDate = QDate::currentDate();
    QTime CurrentTime = QTime::currentTime();
    QString CurrentDateText = CurrentDate.toString("yyyy-MM-dd");//当前日期
    //    QString CurrentDateText = CurrentDate->toString(Qt::ISODate);
    QString CurrentTimeText = CurrentTime.toString("hh:mm");//当前时间
    if(date == CurrentDateText)
    {
        if(time == CurrentTimeText)
        {
//            QSettings settings("Config.ini", QSettings::IniFormat);
//            settings.beginGroup("TIMING");
//            settings.setValue("lastDateShutDown", CurrentDateText);
//            settings.endGroup();
//            system("shutdown -s -t 30");
//            shutDownSwich = true;
//            SysIcon->showMessage("定时关机","系统将于30秒后关机！");
            Shutdown();
            time.end();
        }
    }
}

void MainWindow::TimerEvent(QTimer *timer)
{
    if(shutDownSwich == true)
    {
        system("shutdown -a");//取消关机指令
        shutDownSwich = false;
    }
    if(timer->isActive())//假如定时是启动状态
    {
        timer->stop();  // 关闭定时器
        ui->startBtn->setText("开始");
        ui->dateBox->setEnabled(true);
        ui->timeEdit->setEnabled(true);
        if(dateBoxArg == 1)
        {
            ui->dateEdit->setEnabled(true);
        }
        else if(dateBoxArg == 0)
        {
            ui->dateEdit->setEnabled(false);
        }
//            ui->statusBar->clearMessage();
    }
    else
    {
        SysIcon->showMessage("定时关机","已启动定时关机计划");
        ui->startBtn->setText("关闭");
        timer->start(10000); // 1000ms == 1s
        qDebug() << "开始";
        ui->dateBox->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit->setEnabled(false);
    }
}

void MainWindow::HideShowTiming(QLabel* label)
{
    QString BtnHS = ui->startBtn->text();
    QFont ft;
    QSettings timingConfig("Config.ini", QSettings::IniFormat);
    timingConfig.beginGroup("TIMING");
    if(BtnHS == "关闭"){
        labelWidget->hide();
//        ui->timeDateWidget->show();
        ui->timeWidget->show();
        ui->dateWidget->show();

    }else if(BtnHS == "开始"){
//        ui->timeDateWidget->hide();
        ui->timeWidget->hide();
        ui->dateWidget->hide();
        ui->statusBar->clearMessage();
//        ui->timeEdit->hide();
        QString str("系统将于以下时间关机\n");
        QString strT;
        QString str2;
        label->setAlignment(Qt::AlignCenter);
        label->setFixedWidth(180);
        labelLayout->addStretch();
        labelLayout->addWidget(label);
        labelLayout->addStretch();
        labelWidget->setLayout(labelLayout);
        ui->verticalLayout->addWidget(labelWidget);
        if(dateBoxArg == 1){
            ft.setPointSize(12);
            str.append(timingConfig.value("planDate").toString());
            str += " ";
            label->setGeometry(40,50,180,100);
//            label->setWordWrap(true);//自动换行
        }else if(dateBoxArg == 0)
        {
            ft.setPointSize(13);
            label->move(50, 100);
            label->setGeometry(40,50,180,100);
        }
//        label->adjustSize();//自适应大小
        str2.append(timingConfig.value("planTime").toString());
        timingConfig.endGroup();
        strT = "<p style='line-height:40px; width:100% ; white-space: pre-wrap; '>" + str + str2 + "</p>";
        label->setStyleSheet("QLabel{color:red;}");
        label->setText(strT);
        label->setFont(ft);
        labelWidget->show();
    }
}

/* 执行关机操作 */
void MainWindow::Shutdown()
{
    QDate CurrentDate = QDate::currentDate();
    QString CurrentDateText = CurrentDate.toString("yyyy-MM-dd");//当前日期
    QSettings settings("Config.ini", QSettings::IniFormat);
    settings.beginGroup("TIMING");
    settings.setValue("lastDateShutDown", CurrentDateText);
    settings.endGroup();
    system("shutdown -s -t 30");//30秒后关机
    ui->statusBar->showMessage("您可以点击【关闭】按钮取消关机");
    shutDownSwich = true;
    SysIcon->showMessage("定时关机","系统将于30秒后关机！");
}

void MainWindow::setThisRunTime(int thisRunTime)
{
    _thisRunTime = thisRunTime;
}

void MainWindow::setStatusBarMeg()
{
    QString message = ui->statusBar->currentMessage();
    QString runTimeMsg;
    runTimeMsg.append("运行时间（秒）：");
    runTimeMsg.append(QString::number(_thisRunTime));
    if(message.isEmpty() || message != "您可以点击【关闭】按钮取消关机" || _thisRunTime >= 10)
    {
        ui->statusBar->showMessage(runTimeMsg);
    }
}

void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {

    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}

/* 重写关闭按钮事件 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(SysIcon->isVisible())
    {
        this->hide();
        SysIcon->showMessage("定时关机","程序已最小化到托盘！");
        event->ignore();
    }
    else {
        event->accept();
    }
}

void MainWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/Resources/QSS/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if(!file.isOpen())
    {
        qDebug() << "文件打开失败！";
        return;
    }
    setStyleSheet("");
    QString qsstyleSheet = QLatin1String(file.readAll());
    setStyleSheet(qsstyleSheet);
    file.close();
}

/* 自动启动的可选项被点击时 */
void MainWindow::on_automaticStartBox_clicked()
{
    automatic = ui->automaticStartBox->isChecked();
    QSettings settings("Config.ini", QSettings::IniFormat);
    settings.beginGroup("TIMING");
    settings.setValue("automatic", automatic);
    settings.endGroup();

    qDebug() << "是否设置了自动启动" << automatic;
}

/* 日期开关可选项被点击时 */
void MainWindow::on_dateBox_clicked()
{
    int arg1 = ui->dateBox->isChecked();
    qDebug() << "日期开关：" << arg1;
    //设置配置文件
    QSettings settings("Config.ini", QSettings::IniFormat);
    settings.beginGroup("TIMING");
    settings.setValue("dateBoxArg", arg1);
    settings.endGroup();
    dateBoxArg = arg1;
    //影响日期控件的启用和禁用
    if(arg1 == 1)
    {
        ui->dateEdit->setEnabled(true);
    }
    else if(arg1 == 0)
    {
        ui->dateEdit->setEnabled(false);
    }
}

/* 完成日期编辑时 */
void MainWindow::on_dateEdit_editingFinished()
{
    QString date = ui->dateEdit->text();
    QSettings settings("Config.ini", QSettings::IniFormat);
    settings.beginGroup("TIMING");
    settings.setValue("planDate", date);
    settings.endGroup();
}

/* 完成时间编辑时 */
void MainWindow::on_timeEdit_editingFinished()
{
    QString time = ui->timeEdit->text();
    QSettings settings("Config.ini", QSettings::IniFormat);
    settings.beginGroup("TIMING");
    settings.setValue("planTime", time);
    settings.endGroup();
}

void MainWindow::on_ButtonClose_clicked()
{
    close();
}
