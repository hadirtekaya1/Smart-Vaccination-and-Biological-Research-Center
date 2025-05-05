#ifndef STAT_H
#define STAT_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Stat;
}

class Stat : public QWidget
{
    Q_OBJECT

public:
    explicit Stat(QWidget *parent = nullptr);
    ~Stat();

signals:
    void backRequested();

private slots:
    void on_backButton_clicked();

private:
    Ui::Stat *ui;

    void fetchSuccessRateData();
    void fetchAvgDurationData();
    void fetchComparisonData();
    void setupSuccessRateChart(int successCount, int failureCount);
    void setupAvgDurationChart(double avgDuration);
    void setupComparisonChart(const QList<QString>& responsibles, const QList<int>& successCounts, const QList<int>& failureCounts, const QStringList& protocols);
    void applyShadow(QWidget* widget);
};

#endif // STAT_H
