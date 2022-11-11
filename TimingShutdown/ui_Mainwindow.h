/********************************************************************************
** Form generated from reading UI file 'Mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *titleLabel;
    QPushButton *startBtn;
    QCheckBox *automaticStartBox;
    QWidget *timeDateWidget;
    QVBoxLayout *verticalLayout;
    QWidget *dateWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *dateBox;
    QDateEdit *dateEdit;
    QWidget *timeWidget;
    QHBoxLayout *horizontalLayout_2;
    QTimeEdit *timeEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(255, 252);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(90, 20, 81, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setGeometry(QRect(90, 160, 75, 23));
        automaticStartBox = new QCheckBox(centralwidget);
        automaticStartBox->setObjectName(QString::fromUtf8("automaticStartBox"));
        automaticStartBox->setGeometry(QRect(60, 200, 151, 16));
        timeDateWidget = new QWidget(centralwidget);
        timeDateWidget->setObjectName(QString::fromUtf8("timeDateWidget"));
        timeDateWidget->setGeometry(QRect(40, 60, 179, 100));
        verticalLayout = new QVBoxLayout(timeDateWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dateWidget = new QWidget(timeDateWidget);
        dateWidget->setObjectName(QString::fromUtf8("dateWidget"));
        horizontalLayout = new QHBoxLayout(dateWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        dateBox = new QCheckBox(dateWidget);
        dateBox->setObjectName(QString::fromUtf8("dateBox"));
        dateBox->setEnabled(true);

        horizontalLayout->addWidget(dateBox);

        dateEdit = new QDateEdit(dateWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(true);
        dateEdit->setDateTime(QDateTime(QDate(2022, 9, 14), QTime(0, 0, 0)));
        dateEdit->setMinimumDateTime(QDateTime(QDate(2000, 9, 14), QTime(0, 0, 0)));

        horizontalLayout->addWidget(dateEdit);


        verticalLayout->addWidget(dateWidget);

        timeWidget = new QWidget(timeDateWidget);
        timeWidget->setObjectName(QString::fromUtf8("timeWidget"));
        horizontalLayout_2 = new QHBoxLayout(timeWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        timeEdit = new QTimeEdit(timeWidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));

        horizontalLayout_2->addWidget(timeEdit);


        verticalLayout->addWidget(timeWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\205\263\346\234\272", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        automaticStartBox->setText(QCoreApplication::translate("MainWindow", "\346\257\217\346\254\241\345\274\200\345\220\257\347\250\213\345\272\217\350\207\252\345\212\250\346\211\247\350\241\214", nullptr));
        dateBox->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("MainWindow", "yyyy-MM-dd", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
