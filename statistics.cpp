#include "statistics.h"
#include "ui_statistics.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>

Statistics::Statistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);


    loadStatistics();

    connect(ui->comparisonTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Statistics::on_comparisonTypeComboBox_currentIndexChanged);

    connect(ui->refreshStatsButton, &QPushButton::clicked,
            this, &Statistics::on_refreshStatsButton_clicked);
}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::loadStatistics()
{
    double rate = calculateSuccessRate();
    ui->successRateLabel->setText(QString("Success Rate: %1 %").arg(QString::number(rate, 'f', 2)));

    double avg = calculateAverageDuration();
    ui->averageDurationLabel->setText(QString("Average Duration: %1 days").arg(QString::number(avg, 'f', 1)));

    populateComparisonTable(ui->comparisonTypeComboBox->currentIndex() == 0);
}

double Statistics::calculateSuccessRate()
{
    QSqlQuery total("SELECT COUNT(*) FROM EXPERIMENTS");
    QSqlQuery success("SELECT COUNT(*) FROM EXPERIMENTS WHERE status = 'Success'");

    if (total.next() && success.next()) {
        int t = total.value(0).toInt();
        int s = success.value(0).toInt();
        return (t == 0) ? 0.0 : (s * 100.0 / t);
    }
    return 0.0;
}

double Statistics::calculateAverageDuration()
{
    QSqlQuery q("SELECT start_date, end_date FROM EXPERIMENTS WHERE start_date IS NOT NULL AND end_date IS NOT NULL");
    int totalDays = 0, count = 0;

    while (q.next()) {
        QDate start = q.value(0).toDate();
        QDate end = q.value(1).toDate();
        int days = start.daysTo(end);
        if (days >= 0) {
            totalDays += days;
            count++;
        }
    }

    return (count == 0) ? 0.0 : (totalDays * 1.0 / count);
}

QMap<QString, QPair<int, int>> Statistics::getComparisonData(bool byResponsible)
{
    QString column = byResponsible ? "responsible_name" : "protocol";
    QSqlQuery q(QString("SELECT %1, status FROM EXPERIMENTS").arg(column));
    QMap<QString, QPair<int, int>> data;

    while (q.next()) {
        QString key = q.value(0).toString();
        QString status = q.value(1).toString();

        if (!key.isEmpty()) {
            if (!data.contains(key))
                data[key] = qMakePair(0, 0);

            if (status == "Success")
                data[key].first++;
            else
                data[key].second++;
        }
    }

    return data;
}

void Statistics::populateComparisonTable(bool byResponsible)
{
    QMap<QString, QPair<int, int>> data = getComparisonData(byResponsible);

    ui->comparisonTable->clear();
    ui->comparisonTable->setRowCount(data.size());
    ui->comparisonTable->setColumnCount(3);
    ui->comparisonTable->setHorizontalHeaderLabels(QStringList()
                                                   << (byResponsible ? "Responsible" : "Protocol")
                                                   << "Success"
                                                   << "Failure");

    int row = 0;
    for (auto it = data.begin(); it != data.end(); ++it, ++row) {
        ui->comparisonTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        ui->comparisonTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value().first)));
        ui->comparisonTable->setItem(row, 2, new QTableWidgetItem(QString::number(it.value().second)));
    }

    ui->comparisonTable->resizeColumnsToContents();
}

void Statistics::on_comparisonTypeComboBox_currentIndexChanged(int index)
{
    populateComparisonTable(index == 0);
}

void Statistics::on_refreshStatsButton_clicked()
{
    loadStatistics();
}
