#include "labconsumablesoptimizer.h"
#include "ui_labconsumablesoptimizer.h"
#include <QMessageBox>
#include <QProgressBar>

LabConsumablesOptimizer::LabConsumablesOptimizer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LabConsumablesOptimizer)
{
    ui->setupUi(this);
    populateTable();
    checkStocks();

    //connect(ui->autoOrderButton, &QPushButton::clicked, this, &LabConsumablesOptimizer::on_autoOrderButton_clicked);
}

LabConsumablesOptimizer::~LabConsumablesOptimizer()
{
    delete ui;
}
void LabConsumablesOptimizer::populateTable()
{
    QStringList names = {"Pipettes", "Tubes", "Reagents"};
    QList<int> stocks = {15, 5, 25};
    QList<int> thresholds = {10, 10, 20};

    ui->tableConsumables->setRowCount(names.size());
    ui->tableConsumables->setColumnCount(4);
    ui->tableConsumables->setHorizontalHeaderLabels({"Name", "Current Stock", "Critical Threshold", "Status"});

    for (int i = 0; i < names.size(); ++i) {
        ui->tableConsumables->setItem(i, 0, new QTableWidgetItem(names[i]));
        ui->tableConsumables->setItem(i, 1, new QTableWidgetItem(QString::number(stocks[i])));
        ui->tableConsumables->setItem(i, 2, new QTableWidgetItem(QString::number(thresholds[i])));

        QProgressBar *progress = new QProgressBar();
        progress->setRange(0, thresholds[i] * 2);
        progress->setValue(stocks[i]);

        if (stocks[i] < thresholds[i]) {
            progress->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        } else if (stocks[i] < thresholds[i] * 1.5) {
            progress->setStyleSheet("QProgressBar::chunk { background-color: orange; }");
        } else {
            progress->setStyleSheet("QProgressBar::chunk { background-color: green; }");
        }

        ui->tableConsumables->setCellWidget(i, 3, progress);
    }
}

void LabConsumablesOptimizer::checkStocks()
{
    int rows = ui->tableConsumables->rowCount();
    for (int i = 0; i < rows; ++i) {
        int stock = ui->tableConsumables->item(i, 1)->text().toInt();
        int threshold = ui->tableConsumables->item(i, 2)->text().toInt();
        QString name = ui->tableConsumables->item(i, 0)->text();

        if (stock < threshold) {
            QMessageBox::warning(this, "Stock Alert", QString("%1 stock is below critical level!").arg(name));
        }
    }
}

void LabConsumablesOptimizer::on_autoOrderButton_clicked()
{
    QMessageBox::information(this, "Auto-Order", "Auto-order request sent to the supplier!");
}


void LabConsumablesOptimizer::on_backButton_clicked()
{
    this->close();
    emit backRequested();
}

