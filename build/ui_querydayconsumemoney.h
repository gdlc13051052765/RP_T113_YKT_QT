/********************************************************************************
** Form generated from reading UI file 'querydayconsumemoney.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYDAYCONSUMEMONEY_H
#define UI_QUERYDAYCONSUMEMONEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_QueryDayConsumeMoney
{
public:

    void setupUi(QDialog *QueryDayConsumeMoney)
    {
        if (QueryDayConsumeMoney->objectName().isEmpty())
            QueryDayConsumeMoney->setObjectName(QString::fromUtf8("QueryDayConsumeMoney"));
        QueryDayConsumeMoney->resize(400, 300);

        retranslateUi(QueryDayConsumeMoney);

        QMetaObject::connectSlotsByName(QueryDayConsumeMoney);
    } // setupUi

    void retranslateUi(QDialog *QueryDayConsumeMoney)
    {
        QueryDayConsumeMoney->setWindowTitle(QApplication::translate("QueryDayConsumeMoney", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QueryDayConsumeMoney: public Ui_QueryDayConsumeMoney {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYDAYCONSUMEMONEY_H