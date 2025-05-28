#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
#include <QStringList>
#include <QTableWidgetItem>
#include <QSqlDatabase>    // Add this
#include <QSqlQuery>       // Add this
#include <QSqlError>       // Add this
#include "connection.h"    // Add this
#include "patient.h"
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
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_toggled(bool checked);
    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_10_clicked();
    void onDeleteButtonClicked();
    void onModifyButtonClicked();
    void onSortComboBoxChanged(int index);
    void on_searchButton_clicked();
    void onAddAppointmentClicked();
    void onViewAppointmentsClicked();
    void onDeleteAppointmentClicked();

private:
    Ui::MainWindow *ui;
    int currentEditRow = -1;
    QStringList historyLog;
    void clearForm();
    void addHistoryEntry(const QString &action, const QString &details);
    void showStyledAlert(const QString &title, const QString &message,
                         QMessageBox::Icon icon = QMessageBox::Information,
                         const QString &buttonColor = "#144976");
    void loadVaccineData();
    void updateDeleteButtons();
    void filterTable(const QString &searchText, int column);
    bool matchesSearch(const QTableWidgetItem *item, const QString &searchText);
    bool darkModeEnabled = false;
    QString originalStyleSheet; // Add this to store your original style
    void toggleDarkMode(bool enabled);
    Connection dbConn;
    void loadVaccinesFromDatabase();
    void refreshTable();
    void loadAppointmentsForPatient(const QString &patientId);
    QMap<QString, QList<QVariantMap>> appointmentsData;

    //void initializeTable();
};

#endif // MAINWINDOW_H
