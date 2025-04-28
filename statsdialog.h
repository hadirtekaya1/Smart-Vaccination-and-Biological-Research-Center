#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class StatsDialog;
}
QT_END_NAMESPACE

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(QWidget *parent = nullptr);
    ~StatsDialog();

    void setData(const QMap<QString, int>& vaccineData);

private slots:
    void exportChart();

private:
    Ui::StatsDialog *ui;
    QChart *chart;
    QChartView *chartView;
};

#endif // STATSDIALOG_H
