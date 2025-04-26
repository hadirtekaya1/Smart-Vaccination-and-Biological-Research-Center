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

Stat::Stat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Stat)
{
    ui->setupUi(this);

    setupSuccessRateChart();
    setupAvgDurationChart();
    setupComparisonChart();
    applyShadow(ui->chartSuccessRate);
    applyShadow(ui->chartAvgDuration);
    applyShadow(ui->chartComparison);
}

Stat::~Stat()
{
    delete ui;
}

void Stat::setupSuccessRateChart()
{
    QPieSeries *series = new QPieSeries();
    series->append("Successful", 75);
    series->append("Failed", 25);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Experiment Success Rate");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartSuccessRate->layout()->addWidget(chartView);
}

void Stat::setupAvgDurationChart()
{
    QBarSet *set = new QBarSet("Duration");

    *set << 5 << 8 << 6 << 7;  // Example durations

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Average Experiment Duration");

    QStringList categories;
    categories << "Test A" << "Test B" << "Test C" << "Test D";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 10);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartAvgDuration->layout()->addWidget(chartView);
}

void Stat::setupComparisonChart()
{
    QBarSet *responsibleA = new QBarSet("Dr. A");
    QBarSet *responsibleB = new QBarSet("Dr. B");

    *responsibleA << 3 << 5 << 2;
    *responsibleB << 4 << 7 << 6;

    QBarSeries *series = new QBarSeries();
    series->append(responsibleA);
    series->append(responsibleB);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Results by Responsible");

    QStringList protocols;
    protocols << "Proto A" << "Proto B" << "Proto C";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(protocols);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 10);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartComparison->layout()->addWidget(chartView);
}
void Stat::applyShadow(QWidget* widget) {
    auto* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10.0);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80)); // Ombre douce
    widget->setGraphicsEffect(shadow);
}




void Stat::on_backButton_clicked()
{
    this->close();  // Close the statistics window
    emit backRequested();  // Emit the signal to main window
}

