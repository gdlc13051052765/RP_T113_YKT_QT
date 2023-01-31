/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *startButton;
    QProgressBar *serverProgressBar;
    QLabel *serverStatusLabel;

    void setupUi(QDialog *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(493, 300);
        startButton = new QPushButton(Widget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        startButton->setGeometry(QRect(160, 160, 101, 41));
        QFont font;
        font.setPointSize(16);
        startButton->setFont(font);
        serverProgressBar = new QProgressBar(Widget);
        serverProgressBar->setObjectName(QString::fromUtf8("serverProgressBar"));
        serverProgressBar->setGeometry(QRect(60, 110, 321, 23));
        serverProgressBar->setValue(24);
        serverStatusLabel = new QLabel(Widget);
        serverStatusLabel->setObjectName(QString::fromUtf8("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(70, 70, 311, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QDialog *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Dialog", nullptr));
        startButton->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        serverStatusLabel->setText(QApplication::translate("Widget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
