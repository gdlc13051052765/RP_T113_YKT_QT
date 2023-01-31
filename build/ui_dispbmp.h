/********************************************************************************
** Form generated from reading UI file 'dispbmp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPBMP_H
#define UI_DISPBMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dispBmp
{
public:

    void setupUi(QWidget *dispBmp)
    {
        if (dispBmp->objectName().isEmpty())
            dispBmp->setObjectName(QString::fromUtf8("dispBmp"));
        dispBmp->resize(400, 300);

        retranslateUi(dispBmp);

        QMetaObject::connectSlotsByName(dispBmp);
    } // setupUi

    void retranslateUi(QWidget *dispBmp)
    {
        dispBmp->setWindowTitle(QApplication::translate("dispBmp", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dispBmp: public Ui_dispBmp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPBMP_H
