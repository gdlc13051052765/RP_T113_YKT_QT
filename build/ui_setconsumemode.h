/********************************************************************************
** Form generated from reading UI file 'setconsumemode.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCONSUMEMODE_H
#define UI_SETCONSUMEMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_setConsumeMode
{
public:

    void setupUi(QDialog *setConsumeMode)
    {
        if (setConsumeMode->objectName().isEmpty())
            setConsumeMode->setObjectName(QString::fromUtf8("setConsumeMode"));
        setConsumeMode->resize(400, 300);

        retranslateUi(setConsumeMode);

        QMetaObject::connectSlotsByName(setConsumeMode);
    } // setupUi

    void retranslateUi(QDialog *setConsumeMode)
    {
        setConsumeMode->setWindowTitle(QApplication::translate("setConsumeMode", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setConsumeMode: public Ui_setConsumeMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCONSUMEMODE_H
