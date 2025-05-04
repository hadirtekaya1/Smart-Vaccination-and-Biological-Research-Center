#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DatabaseManager.h"
#include <QMainWindow>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QSqlTableModel;
class QString;
class QComboBox;
class QLabel;
class QDateEdit;
class QLineEdit;
class QPushButton;
class QTableView;
class QStackedWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();
    void on_deleteEquipButton_2_clicked();

    void onUpdateTableSelectionChanged(const QModelIndex &current, const QModelIndex &previous);
    void onAddConsumableChanged(const QString &text);
    void onUpdateConsumableChanged(const QString &text);

    void onSearchTextChanged(const QString &searchText);
    void onUpdateSearchTextChanged(const QString &searchText);
    void on_searchTextBox_2_textChanged(const QString &searchText);

    void on_export_2_clicked();


private:
    Ui::MainWindow *ui;
    QString m_selectedUpdateId;
    QWidget *widget;
    QSqlTableModel *m_mainModel;
    QSqlTableModel *m_updateModel;
    QSqlTableModel *m_deleteModel;

    void setupNavigationAndConnections();
    void loadEquipmentTable();
    void loadUpdateEquipmentTable();
    void loadDeleteEquipmentTable();
    void applyFilter(QSqlTableModel *model, const QString &searchText);
    void updateDashboardCounts();
    QString escapeCsv(const QString &input);
    void showStatsChart();

};
#endif // MAINWINDOW_H
