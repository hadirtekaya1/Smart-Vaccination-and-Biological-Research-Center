// statsdialog.cpp
#include "statsdialog.h"
#include "ui_statsdialog.h"
#include <QPixmap>
#include <QDir>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>

StatsDialog::StatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog),
    chart(new QChart()),
    chartView(new QChartView(chart))
{
    ui->setupUi(this);
    this->setWindowTitle("Patient Statistics");
    this->setMinimumSize(800, 600);

    // Chart configuration
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setMargins(QMargins(10, 10, 10, 10));

    // Add chart to layout
    ui->verticalLayout->insertWidget(0, chartView, 1);

    // Button styling
    ui->btnExport->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 16px;"
        "  background-color: #144976;"
        "  color: white;"
        "  border-radius: 4px;"
        "}"
        "QPushButton:hover { background-color: #1a5a8f; }"
        );

    ui->btnClose->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 16px;"
        "  background-color: #6c757d;"
        "  color: white;"
        "  border-radius: 4px;"
        "}"
        "QPushButton:hover { background-color: #5a6268; }"
        );

    // Connect buttons
    connect(ui->btnExport, &QPushButton::clicked, this, &StatsDialog::exportChart);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::reject);
}

void StatsDialog::setPatientData(const QMap<QString, int>& patientData)
{
    chart->removeAllSeries();
    if (patientData.isEmpty()) return;

    QBarSeries *series = new QBarSeries();
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

    // Sort by count (descending)
    QList<QPair<QString, int>> sortedData;
    for (auto it = patientData.begin(); it != patientData.end(); ++it) {
        sortedData.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedData.begin(), sortedData.end(),
              [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
                  return a.second > b.second;
              });

    // Create bars
    for (const auto& item : sortedData) {
        QBarSet *set = new QBarSet(item.first);
        *set << item.second;
        set->setLabelColor(Qt::black);
        series->append(set);
    }

    chart->addSeries(series);
    chart->setTitle("Patient Statistics by Gender");
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Configure axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("Categories");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Configure legend
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Arial", 9));
}

void StatsDialog::setMonthlyPatientData(const QMap<QString, int>& monthlyData)
{
    chart->removeAllSeries();
    if (chart->axisX()) chart->removeAxis(chart->axisX());
    if (chart->axisY()) chart->removeAxis(chart->axisY());

    if (monthlyData.isEmpty()) return;

    QLineSeries *series = new QLineSeries();
    series->setName("Patients");

    // Optional: Smooth the curve
    series->setUseOpenGL(false);         // Use normal CPU rendering for smoother curves
    series->setPointsVisible(true);       // Show points (dots)
    series->setPointLabelsVisible(true);  // Show labels
    series->setPointLabelsFormat("@yPoint"); // Only Y values

    // Sort months chronologically
    QMap<QDate, int> sortedData;
    for (auto it = monthlyData.begin(); it != monthlyData.end(); ++it) {
        QDate date = QDate::fromString(it.key(), "MMMM yyyy");
        if (date.isValid()) {
            sortedData[date] = it.value();
        }
    }

    // Add points to the line series
    for (auto it = sortedData.begin(); it != sortedData.end(); ++it) {
        QDateTime dateTime(it.key(), QTime(0, 0));
        series->append(dateTime.toMSecsSinceEpoch(), it.value());
    }

    chart->addSeries(series);
    chart->setTitle("Patient Registrations by Month");

    // Configure X-axis (time axis)
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Month");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configure Y-axis (number of patients)
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Number of Patients");

    int maxValue = 0;
    for (const auto &value : sortedData.values()) {
        if (value > maxValue) maxValue = value;
    }
    axisY->setRange(0, maxValue + 1);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Final formatting
    chart->legend()->setVisible(false);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void StatsDialog::exportChart()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Chart as Image",
        QDir::homePath() + "/vaccine_stats.png",
        "PNG Image (*.png);;JPEG Image (*.jpg);;PDF (*.pdf)"
        );

    if (!fileName.isEmpty()) {
        QPixmap pixmap = chartView->grab();
        if (pixmap.save(fileName)) {
            QMessageBox::information(this, "Success", "Chart saved successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save chart.");
        }
    }
}

StatsDialog::~StatsDialog()
{
    delete ui;
}
