#include "stat.h"
#include "ui_stat.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QGraphicsDropShadowEffect>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Stat::Stat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Stat)
{
    ui->setupUi(this);

    // Fetch and populate the charts with data
    fetchSuccessRateData();
    fetchAvgDurationData();
    fetchComparisonData();

    // Apply shadows to the charts
    applyShadow(ui->chartSuccessRate);
    applyShadow(ui->chartAvgDuration);
    applyShadow(ui->chartComparison);
}

Stat::~Stat()
{
    delete ui;
}

void Stat::fetchSuccessRateData()
{
    QSqlQuery query;
    query.prepare("SELECT SUM(CASE WHEN RESULTS_OBTAINED = 'Success' THEN 1 ELSE 0 END) AS successCount, "
                  "SUM(CASE WHEN RESULTS_OBTAINED = 'Failure' THEN 1 ELSE 0 END) AS failureCount "
                  "FROM experiments");
    if (!query.exec()) {
        qDebug() << "Error fetching success rate data: " << query.lastError();
        return;
    }

    if (query.next()) {
        int successCount = query.value(0).toInt();
        int failureCount = query.value(1).toInt();

        setupSuccessRateChart(successCount, failureCount);
    }
}

void Stat::fetchAvgDurationData()
{
    QSqlQuery query;
    query.prepare("SELECT AVG(END_DATE - START_DATE) AS avgDuration FROM experiments");
    if (!query.exec()) {
        qDebug() << "Error fetching average duration data: " << query.lastError();
        return;
    }

    if (query.next()) {
        double avgDuration = query.value(0).toDouble();
        setupAvgDurationChart(avgDuration);
    }
}

void Stat::fetchComparisonData()
{
    // Fetch distinct protocols from the database
    QSqlQuery protocolQuery;
    protocolQuery.prepare("SELECT DISTINCT PROTOCOL FROM experiments");
    protocolQuery.exec();

    QStringList protocols;
    while (protocolQuery.next()) {
        protocols.append(protocolQuery.value(0).toString());
    }

    // Fetch the success and failure counts for each responsible person
    QSqlQuery query;
    query.prepare("SELECT RESPONSIBLE_NAME, "
                  "SUM(CASE WHEN RESULTS_OBTAINED = 'Success' THEN 1 ELSE 0 END) AS successCount, "
                  "SUM(CASE WHEN RESULTS_OBTAINED = 'Failure' THEN 1 ELSE 0 END) AS failureCount "
                  "FROM experiments GROUP BY RESPONSIBLE_NAME");
    if (!query.exec()) {
        qDebug() << "Error fetching comparison data: " << query.lastError();
        return;
    }

    QList<QString> responsibles;
    QList<int> successCounts;
    QList<int> failureCounts;

    while (query.next()) {
        responsibles.append(query.value(0).toString());
        successCounts.append(query.value(1).toInt());
        failureCounts.append(query.value(2).toInt());
    }

    // Now setup the comparison chart with the dynamic protocol list
    setupComparisonChart(responsibles, successCounts, failureCounts, protocols);
}

void Stat::setupSuccessRateChart(int successCount, int failureCount)
{
    QPieSeries *series = new QPieSeries();
    series->append("Successful", successCount);
    series->append("Failed", failureCount);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Experiment Success Rate");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartSuccessRate->layout()->addWidget(chartView);
}

void Stat::setupAvgDurationChart(double avgDuration)
{
    QBarSet *set = new QBarSet("Average Duration");
    *set << avgDuration;

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Average Experiment Duration");

    QStringList categories;
    categories << "Average Duration";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 20);  // Adjust this range based on expected duration
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartAvgDuration->layout()->addWidget(chartView);
}

void Stat::setupComparisonChart(const QList<QString>& responsibles, const QList<int>& successCounts, const QList<int>& failureCounts, const QStringList& protocols)
{
    QBarSeries *series = new QBarSeries();

    for (int i = 0; i < responsibles.size(); ++i) {
        QBarSet *setSuccess = new QBarSet(responsibles[i] + " Success");
        *setSuccess << successCounts[i];

        QBarSet *setFailure = new QBarSet(responsibles[i] + " Failure");
        *setFailure << failureCounts[i];

        series->append(setSuccess);
        series->append(setFailure);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Results by Responsible");

    // Use dynamic protocols for the X-axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(protocols);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 10);  // Adjust this range based on your actual data
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartComparison->layout()->addWidget(chartView);
}

void Stat::applyShadow(QWidget* widget)
{
    auto* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10.0);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80)); // Soft shadow
    widget->setGraphicsEffect(shadow);
}

void Stat::on_backButton_clicked()
{
    this->close();  // Close the statistics window
    emit backRequested();  // Emit the signal to main window
}
