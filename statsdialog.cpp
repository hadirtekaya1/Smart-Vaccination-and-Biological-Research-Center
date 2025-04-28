#include "statsdialog.h"
#include "ui_statsdialog.h"
#include <QPixmap>
#include <QDir>

StatsDialog::StatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog),
    chart(new QChart()),
    chartView(new QChartView(chart))
{
    ui->setupUi(this);
    this->setWindowTitle("Vaccine Statistics");
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

void StatsDialog::setData(const QMap<QString, int>& vaccineData)
{
    chart->removeAllSeries();
    if (vaccineData.isEmpty()) return;

    QBarSeries *series = new QBarSeries();
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

    // Sort by stock quantity (descending)
    QList<QPair<QString, int>> sortedData;
    for (auto it = vaccineData.begin(); it != vaccineData.end(); ++it) {
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
    chart->setTitle("Vaccine Stock Quantities");
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Configure axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("Vaccines");
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
