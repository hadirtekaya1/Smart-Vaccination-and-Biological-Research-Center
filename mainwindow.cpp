#include "mainwindow.h"
#include "experiments.h"
#include "ui_mainwindow.h"
#include "resultshistory.h"
#include "statistics.h"
#include "stat.h"
#include "labconsumablesoptimizer.h"
#include <QMessageBox>
#include <QDate>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imageLabel->setFixedSize(200, 200);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(QPixmap(":/images/scientist.png"));
    Experiments exp;
    ui->tableView->setModel(exp.read());

    // Ajustement de la taille des colonnes pour s'adapter au contenu
    ui->tableView->resizeColumnsToContents();
    ui->startDateLineEdit->setMinimumDate(QDate::currentDate());
    ui->endDateLineEdit->setMinimumDate(QDate::currentDate());
    ui->startDateUpdatedLineEdit->setMinimumDate(QDate::currentDate());
    ui->endDateUpdatedLineEdit->setMinimumDate(QDate::currentDate());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    // Get values from UI
    int id = ui->experimentIdLineEdit->text().toInt();
    QString name = ui->experimentNameLineEdit->text();
    QString desc = ui->descriptionLineEdit->text();
    QString protocol = ui->protocolLineEdit->text();
    QString status = ui->statusComboBox->currentText();
    QDate startDate = ui->startDateLineEdit->date();
    QDate endDate = ui->endDateLineEdit->date();
    QString results_obtained = ui->resultsObtainedLineEdit->text();
    QString responsible_name = ui->responsibleNameLineEdit->text();

    if (startDate < QDate::currentDate() || endDate < QDate::currentDate()) {
        QMessageBox::warning(this, "Invalid Date", "Start and end dates must be today or in the future.");
        return; // empêche de continuer
    }


    // Create Experiments object
    Experiments exp(id, name, desc, protocol, status, startDate, endDate, results_obtained, responsible_name);

    // Attempt to add to database
    bool test = exp.add();

    // Show result message
    if(test) {
        ui->tableView->setModel(exp.read());
        QMessageBox::information(nullptr, QObject::tr("Success"),
                                 QObject::tr("Experiment added successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        refreshExperimentTable();
        clearForm();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Failed to add experiment.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::clearForm()
{
    ui->experimentIdLineEdit->clear();
    ui->experimentNameLineEdit->clear();
    ui->descriptionLineEdit->clear();
    ui->protocolLineEdit->clear();
    ui->statusComboBox->setCurrentIndex(0);
    ui->startDateLineEdit->setDate(QDate::currentDate());
    ui->endDateLineEdit->setDate(QDate::currentDate().addDays(30));
    ui->experimentIdRemovedLineEdit->clear();
    ui->experimentIdUpdatedLineEdit->clear();
    ui->protocolUpdatedLineEdit->clear();
    ui->experimentNameUpdtaedLineEdit->clear();
    ui->descriptionUpdatedLineEdit->clear();
    ui->statusUpdtaedComboBox->setCurrentIndex(0);
    ui->startDateUpdatedLineEdit->setDate(QDate::currentDate());
    ui->endDateUpdatedLineEdit->setDate(QDate::currentDate().addDays(30));
    ui->resultsObtainedLineEdit->clear();
    ui->resultsObtainedUpdatedLineEdit->clear();
    ui->responsibleNameLineEdit->clear();
    ui->responsibleNameUpdatedLineEdit->clear();

}


void MainWindow::on_deleteButton_clicked()
{
    int id = ui->experimentIdRemovedLineEdit->text().toInt();
    Experiments exp;

    bool test = exp.remove(id);  // ← une seule fois

    if (test) {
        QMessageBox::information(this, "Success", "Experiment deleted successfully");
        refreshExperimentTable();
        clearForm();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete experiment");
    }
}

void MainWindow::refreshExperimentTable()
{
    Experiments exp;
    QSqlQueryModel *model = exp.read();
    ui->tableView->setModel(model);
}





void MainWindow::on_updateButton_clicked()
{
    // Get values from UI
    int id = ui->experimentIdUpdatedLineEdit->text().toInt();
    QString name = ui->experimentNameUpdtaedLineEdit->text();
    QString desc = ui->descriptionUpdatedLineEdit->text();
    QString protocol = ui->protocolUpdatedLineEdit->text();
    QString status = ui->statusUpdtaedComboBox->currentText();
    QDate startDate = ui->startDateUpdatedLineEdit->date();
    QDate endDate = ui->endDateUpdatedLineEdit->date();
    QString results_obtained =ui->resultsObtainedUpdatedLineEdit->text();
    QString responsible_name = ui->responsibleNameUpdatedLineEdit->text();

    if (startDate < QDate::currentDate() || endDate < QDate::currentDate()) {
        QMessageBox::warning(this, "Invalid Date", "Start and end dates must be today or in the future.");
        return; // empêche de continuer
    }


    Experiments exp;

    // Appeler la méthode update avec les bons paramètres
    bool test = exp.update(id, name, desc, protocol, status, startDate, endDate, results_obtained, responsible_name);

    if(test) {
        ui->tableView->setModel(exp.read());  // Rafraîchir le tableau
        QMessageBox::information(nullptr, QObject::tr("Success"),
                                 QObject::tr("Experiment updated successfully.\n"

                                             "Click Cancel to exit."), QMessageBox::Cancel);
        refreshExperimentTable();
        clearForm();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Failed to update experiment.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_resultsHistoryButton_clicked()
{
    this->hide();
    ResultsHistory *historyWindow = new ResultsHistory(nullptr); // No parent
    historyWindow->setWindowFlags(Qt::Window);
    connect(historyWindow, &ResultsHistory::backRequested, this, &MainWindow::show);
    historyWindow->show();
}



void MainWindow::on_labConsumablesOptimizerButton_clicked()
{
    this->hide();
    LabConsumablesOptimizer *optimizerWindow = new LabConsumablesOptimizer(nullptr); // No parent
    optimizerWindow ->setWindowFlags(Qt::Window);
    connect(optimizerWindow, &LabConsumablesOptimizer::backRequested, this, &MainWindow::show);
    optimizerWindow ->show();

}


void MainWindow::on_statisticsButton_clicked()
{
    this->hide();
    Statistics *statisticsWindow = new Statistics (nullptr); // No parent
    statisticsWindow->setWindowFlags(Qt::Window);
    connect(statisticsWindow, &Statistics::backRequested, this, &MainWindow::show);
    statisticsWindow ->show();

}





void MainWindow::on_statButton_clicked()
{
    this->hide();
    Stat *statWindow = new Stat (nullptr);
    statWindow->setWindowFlags(Qt::Window);
    connect(statWindow, &Stat::backRequested, this, &MainWindow::show);
    statWindow->show();

}

