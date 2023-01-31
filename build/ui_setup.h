/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>

QT_BEGIN_NAMESPACE

class Ui_setUp
{
public:
    QGroupBox *groupBox;

    void setupUi(QDialog *setUp)
    {
        if (setUp->objectName().isEmpty())
            setUp->setObjectName(QString::fromUtf8("setUp"));
        setUp->resize(455, 300);
        groupBox = new QGroupBox(setUp);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(170, 110, 120, 80));

        retranslateUi(setUp);

        QMetaObject::connectSlotsByName(setUp);
    } // setupUi

    void retranslateUi(QDialog *setUp)
    {
        setUp->setWindowTitle(QApplication::translate("setUp", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("setUp", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setUp: public Ui_setUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
