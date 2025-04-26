#ifndef STAT_H
#define STAT_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

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

    void setupSuccessRateChart();
    void setupAvgDurationChart();
    void setupComparisonChart();
    void applyShadow(QWidget* widget);
};

#endif // STAT_H
