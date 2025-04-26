#ifndef Statistics_H
#define Statistics_H

#include <QWidget>
#include <QSqlQuery>
#include <QMap>

namespace Ui {
class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();

signals:
    void backRequested();

private slots:
    void loadStatistics();
    void on_comparisonTypeComboBox_currentIndexChanged(int index);
    void on_refreshStatsButton_clicked();

private:
    Ui::Statistics *ui;

    double calculateSuccessRate();
    double calculateAverageDuration();
    QMap<QString, QPair<int, int>> getComparisonData(bool byResponsible);
    void populateComparisonTable(bool byResponsible);
};

#endif // Statistics_H
