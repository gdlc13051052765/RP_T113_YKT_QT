/********************************************************************************
** Form generated from reading UI file 'mainconsumewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCONSUMEWINDOW_H
#define UI_MAINCONSUMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainConsumeWindow
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainConsumeWindow)
    {
        if (MainConsumeWindow->objectName().isEmpty())
            MainConsumeWindow->setObjectName(QString::fromUtf8("MainConsumeWindow"));
        MainConsumeWindow->resize(800, 600);
        menubar = new QMenuBar(MainConsumeWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MainConsumeWindow->setMenuBar(menubar);
        centralwidget = new QWidget(MainConsumeWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainConsumeWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainConsumeWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainConsumeWindow->setStatusBar(statusbar);

        retranslateUi(MainConsumeWindow);

        QMetaObject::connectSlotsByName(MainConsumeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainConsumeWindow)
    {
        MainConsumeWindow->setWindowTitle(QApplication::translate("MainConsumeWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainConsumeWindow: public Ui_MainConsumeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCONSUMEWINDOW_H
