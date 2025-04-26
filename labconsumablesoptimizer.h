#ifndef LABCONSUMABLESOPTIMIZER_H
#define LABCONSUMABLESOPTIMIZER_H

#include <QWidget>

namespace Ui {
class LabConsumablesOptimizer;
}

class LabConsumablesOptimizer : public QWidget
{
    Q_OBJECT

public:
    explicit LabConsumablesOptimizer(QWidget *parent = nullptr);
    ~LabConsumablesOptimizer();

signals:
    void backRequested();

private slots:
    void checkStocks();
    void on_autoOrderButton_clicked();

    void on_backButton_clicked();

private:
    Ui::LabConsumablesOptimizer *ui;
    void populateTable();
};

#endif // LABCONSUMABLESOPTIMIZER_H
