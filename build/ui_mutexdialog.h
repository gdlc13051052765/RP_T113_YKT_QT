/********************************************************************************
** Form generated from reading UI file 'mutexdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTEXDIALOG_H
#define UI_MUTEXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_mutexDialog
{
public:

    void setupUi(QDialog *mutexDialog)
    {
        if (mutexDialog->objectName().isEmpty())
            mutexDialog->setObjectName(QString::fromUtf8("mutexDialog"));
        mutexDialog->resize(400, 300);

        retranslateUi(mutexDialog);

        QMetaObject::connectSlotsByName(mutexDialog);
    } // setupUi

    void retranslateUi(QDialog *mutexDialog)
    {
        mutexDialog->setWindowTitle(QApplication::translate("mutexDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mutexDialog: public Ui_mutexDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTEXDIALOG_H
