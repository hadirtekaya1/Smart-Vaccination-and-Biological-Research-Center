/********************************************************************************
** Form generated from reading UI file 'historydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYDIALOG_H
#define UI_HISTORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HistoryDialog
{
public:
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *HistoryDialog)
    {
        if (HistoryDialog->objectName().isEmpty())
            HistoryDialog->setObjectName("HistoryDialog");
        HistoryDialog->resize(600, 500);
        verticalLayout = new QVBoxLayout(HistoryDialog);
        verticalLayout->setObjectName("verticalLayout");
        listView = new QListView(HistoryDialog);
        listView->setObjectName("listView");
        listView->setStyleSheet(QString::fromUtf8("QListView {\n"
"    font-family: Consolas, monospace;\n"
"    font-size: 11pt;\n"
"    background-color: #f8f9fa;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"}\n"
"QListView::item {\n"
"    padding: 5px;\n"
"    border-bottom: 1px solid #dee2e6;\n"
"}\n"
"QListView::item:hover {\n"
"    background-color: #e9ecef;\n"
"}\n"
"color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnClear = new QPushButton(HistoryDialog);
        btnClear->setObjectName("btnClear");
        btnClear->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #dc3545;\n"
"    color: white;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #c82333;\n"
"}"));

        horizontalLayout->addWidget(btnClear);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(HistoryDialog);
        btnClose->setObjectName("btnClose");
        btnClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #6c757d;\n"
"    color: white;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5a6268;\n"
"}"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(HistoryDialog);
        QObject::connect(btnClose, &QPushButton::clicked, HistoryDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(HistoryDialog);
    } // setupUi

    void retranslateUi(QDialog *HistoryDialog)
    {
        HistoryDialog->setWindowTitle(QCoreApplication::translate("HistoryDialog", "Vaccine History Log", nullptr));
        btnClear->setText(QCoreApplication::translate("HistoryDialog", "Clear History", nullptr));
        btnClose->setText(QCoreApplication::translate("HistoryDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryDialog: public Ui_HistoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYDIALOG_H
