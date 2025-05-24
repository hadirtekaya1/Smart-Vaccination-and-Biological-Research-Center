/********************************************************************************
** Form generated from reading UI file 'statsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSDIALOG_H
#define UI_STATSDIALOG_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StatsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QChartView *chartView;
    QHBoxLayout *hboxLayout;
    QPushButton *btnExport;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *StatsDialog)
    {
        if (StatsDialog->objectName().isEmpty())
            StatsDialog->setObjectName("StatsDialog");
        StatsDialog->resize(800, 600);
        StatsDialog->setStyleSheet(QString::fromUtf8("background-color: white;"));
        verticalLayout = new QVBoxLayout(StatsDialog);
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        verticalLayout->setObjectName("verticalLayout");
        chartView = new QChartView(StatsDialog);
        chartView->setObjectName("chartView");

        verticalLayout->addWidget(chartView);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        btnExport = new QPushButton(StatsDialog);
        btnExport->setObjectName("btnExport");

        hboxLayout->addWidget(btnExport);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(StatsDialog);
        btnClose->setObjectName("btnClose");

        hboxLayout->addWidget(btnClose);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(StatsDialog);

        QMetaObject::connectSlotsByName(StatsDialog);
    } // setupUi

    void retranslateUi(QDialog *StatsDialog)
    {
        StatsDialog->setWindowTitle(QCoreApplication::translate("StatsDialog", "Vaccine Statistics", nullptr));
        btnExport->setText(QCoreApplication::translate("StatsDialog", "Export Chart", nullptr));
        btnClose->setText(QCoreApplication::translate("StatsDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatsDialog: public Ui_StatsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSDIALOG_H
