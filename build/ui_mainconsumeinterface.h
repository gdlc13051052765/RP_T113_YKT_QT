/********************************************************************************
** Form generated from reading UI file 'mainconsumeinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCONSUMEINTERFACE_H
#define UI_MAINCONSUMEINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_mainConsumeInterface
{
public:

    void setupUi(QDialog *mainConsumeInterface)
    {
        if (mainConsumeInterface->objectName().isEmpty())
            mainConsumeInterface->setObjectName(QString::fromUtf8("mainConsumeInterface"));
        mainConsumeInterface->resize(400, 300);

        retranslateUi(mainConsumeInterface);

        QMetaObject::connectSlotsByName(mainConsumeInterface);
    } // setupUi

    void retranslateUi(QDialog *mainConsumeInterface)
    {
        mainConsumeInterface->setWindowTitle(QApplication::translate("mainConsumeInterface", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainConsumeInterface: public Ui_mainConsumeInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCONSUMEINTERFACE_H
