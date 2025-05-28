#include "historydialog.h"
#include "ui_historydialog.h"
#include <QMessageBox>
#include <QPushButton>

HistoryDialog::HistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog),
    model(new QStringListModel(this))
{
    ui->setupUi(this);
    setWindowTitle("Vaccine History Log");
    resize(800, 500);

    // Configure list view
    ui->listView->setModel(model);
    ui->listView->setStyleSheet(
        "QListView {"
        "   font-family: Consolas, monospace;"
        "   font-size: 11pt;"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 4px;"
        "   padding: 5px;"
        "}"
        "QListView::item {"
        "   padding: 5px;"
        "   border-bottom: 1px solid #dee2e6;"
        "}"
        "QListView::item:hover {"
        "   background-color: #e9ecef;"
        "}"
        );

    // Style and connect Close button
    ui->btnClose->setStyleSheet(
        "QPushButton {"
        "   background-color: #6c757d;"
        "   color: white;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #5a6268;"
        "}"
        );
    connect(ui->btnClose, &QPushButton::clicked, this, &HistoryDialog::on_btnClose_clicked);

    // Style and connect Clear button
    ui->btnClear->setStyleSheet(
        "QPushButton {"
        "   background-color: #dc3545;"
        "   color: white;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c82333;"
        "}"
        );
}

void HistoryDialog::setHistory(const QStringList &history)
{
    model->setStringList(history);
}

void HistoryDialog::on_btnClose_clicked()
{
    this->accept();
}

void HistoryDialog::on_btnClear_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear History",
                                  "Are you sure you want to clear the history log?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        model->setStringList(QStringList());
        emit historyCleared();
    }
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}
