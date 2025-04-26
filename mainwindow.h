#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "experiments.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void clearForm();
    void refreshExperimentTable();

    void on_updateButton_clicked();

    void on_resultsHistoryButton_clicked();

    void on_labConsumablesOptimizerButton_clicked();

    void on_statisticsButton_clicked();

    void on_settingsButton_clicked();

    void on_statButton_clicked();

private:
    Ui::MainWindow *ui;
    Experiments exp;
};
#endif // MAINWINDOW_H
