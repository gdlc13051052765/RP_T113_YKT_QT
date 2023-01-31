/********************************************************************************
** Form generated from reading UI file 'udpsocketdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPSOCKETDIALOG_H
#define UI_UDPSOCKETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_udpSocketDialog
{
public:

    void setupUi(QDialog *udpSocketDialog)
    {
        if (udpSocketDialog->objectName().isEmpty())
            udpSocketDialog->setObjectName(QString::fromUtf8("udpSocketDialog"));
        udpSocketDialog->resize(400, 300);

        retranslateUi(udpSocketDialog);

        QMetaObject::connectSlotsByName(udpSocketDialog);
    } // setupUi

    void retranslateUi(QDialog *udpSocketDialog)
    {
        udpSocketDialog->setWindowTitle(QApplication::translate("udpSocketDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class udpSocketDialog: public Ui_udpSocketDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPSOCKETDIALOG_H
