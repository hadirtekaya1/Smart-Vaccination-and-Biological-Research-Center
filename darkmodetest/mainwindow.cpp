#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statsdialog.h"
#include "pdfexporter.h"
#include "historydialog.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
#include <QDate>
#include <QColor>
#include <QTimer>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QBuffer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentEditRow(-1)
{

    ui->setupUi(this);
    QTimer::singleShot(0, this, [this]() {
        loadVaccinesFromDatabase();  // ✅ This runs AFTER the UI is ready
    });


    // Load initial data

    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("sort by");
    ui->comboBox_4->addItem("Patient ID");
    ui->comboBox_4->addItem("First name");
    ui->comboBox_4->addItem("AGE");
    ui->comboBox_4->addItem("Gender");

    // Initialize table columns - add "Action" column for delete button

    QStringList headers = {"Patient ID", "First Name", "Last Name",
                           "Gender", "Date of Birth",
                           "Address", "Email", "Phone Number", "Action"};
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Set column widths
    ui->tableWidget->setColumnWidth(0, 100);  // ID
    ui->tableWidget->setColumnWidth(1, 120);  // First Name
    ui->tableWidget->setColumnWidth(2, 120);  // Last Name
    ui->tableWidget->setColumnWidth(3, 80);   // Gender
    ui->tableWidget->setColumnWidth(4, 120);  // DOB
    ui->tableWidget->setColumnWidth(5, 200);  // Address
    ui->tableWidget->setColumnWidth(6, 150);  // Email
    ui->tableWidget->setColumnWidth(7, 120);  // Phone
    ui->tableWidget->setColumnWidth(8, 150);   // Action

    ui->tableWidget->horizontalHeader()->setFixedHeight(40);
    ui->tableWidget->setSortingEnabled(true);

    // Initialize combo boxes

    ui->comboBox_2->addItems({"M", "F"});
    connect(ui->comboBox_4, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSortComboBoxChanged);

    // Connect radio buttons

    // Connect search button
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    // Connect Enter key in search line edit
    connect(ui->lineEdit_4, &QLineEdit::returnPressed, this, &MainWindow::on_searchButton_clicked);
    //555555555555
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this]() {
        ui->lineEdit_4->clear();
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            ui->tableWidget->setRowHidden(row, false);
        }
        statusBar()->showMessage("Search cleared", 2000);
    });
    // After ui->setupUi(this);
    // Connect Add Appointment
    connect(ui->addAppointmentButton, &QPushButton::clicked,
            this, &MainWindow::onAddAppointmentClicked);

    // Connect View Appointments
    connect(ui->viewAppointmentsButton, &QPushButton::clicked,
            this, &MainWindow::onViewAppointmentsClicked);
    // Add them to your layout or toolbar

    originalStyleSheet = this->styleSheet();
    connect(ui->pushButton_9, &QPushButton::clicked, [this]() {
        darkModeEnabled = !darkModeEnabled;
        toggleDarkMode(darkModeEnabled);
    });

    // Set initial state
    ui->radioButton->setChecked(true);  // Add mode by default
    ui->pushButton->setText("Add");
}
void MainWindow::loadVaccinesFromDatabase()
{
    // Clear existing rows
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(9);

    // Get data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENTS");

    if (model->lastError().isValid()) {
        qCritical() << "Failed to load patients:" << model->lastError().text();
        delete model;
        return;
    }

    // Populate the table
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < 8; ++col) {
            QString value = model->data(model->index(row, col)).toString();

            // Fix date format in column 4 (Date of Birth)
            if (col == 4) {
                // Handle both "2025-01-01T00:00:00.000" and "2025-01-01" formats
                value = value.split("T").first(); // Takes just the date part
            }

            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(row, col, item);
        }

        // Keep all existing button code exactly the same
        QWidget *buttonWidget = new QWidget();
        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
        buttonLayout->setContentsMargins(5, 2, 5, 2);
        buttonLayout->setSpacing(5);

        QPushButton *modifyButton = new QPushButton("Modify");
        modifyButton->setIcon(QIcon("C:/Users/DELL-5430/Downloads/editer.png"));
        modifyButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #17a2b8;"
            "   color: white;"
            "   padding: 5px;"
            "   border-radius: 4px;"
            "   min-width: 40px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #138496;"
            "}");
        modifyButton->setProperty("row", row);
        connect(modifyButton, &QPushButton::clicked, this, &MainWindow::onModifyButtonClicked);

        QPushButton *deleteButton = new QPushButton("Delete");
        deleteButton->setIcon(QIcon("C:/Users/DELL-5430/Downloads/supprimer.png"));
        deleteButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #dc3545;"
            "   color: white;"
            "   padding: 5px;"
            "   border-radius: 4px;"
            "   min-width: 40px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #c82333;"
            "}");
        deleteButton->setProperty("row", row);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);

        buttonLayout->addWidget(modifyButton);
        buttonLayout->addWidget(deleteButton);
        buttonWidget->setLayout(buttonLayout);

        ui->tableWidget->setCellWidget(row, 8, buttonWidget);
        qDebug() << "First 5 dates:";
        for (int i = 0; i < qMin(5, ui->tableWidget->rowCount()); i++) {
            qDebug() << ui->tableWidget->item(i, 4)->text();
        }
    }

    delete model;
}
void MainWindow::refreshTable()
{
    loadVaccinesFromDatabase();
}

void MainWindow::clearForm()
{
    ui->lineEdit_2->clear();//first
    ui->lastnameln->clear();//last
    ui->comboBox_2->setCurrentIndex(0);//gender
    ui->dateEdit_2->setDate(QDate(2025, 1, 1));//birth
    ui->lineEdit_3->clear();//adress
    ui->emailln->clear();//email
    ui->phoneln->clear();//phone
}


void MainWindow::addHistoryEntry(const QString &action, const QString &details)
{
    QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]");
    QString entry;

    // Color code different types of entries
    if (action == "ADD") {
        entry = QString("%1 <span style='color:black;'>: %3</span>")
        .arg(timestamp, details);
    }
    else if (action == "MODIFY") {
        entry = QString("%1 <span style='color:black;'>%2: %3</span>")
        .arg(timestamp, action, details);
    }
    else if (action == "EXPIRED" || action == "OUT OF STOCK") {
        entry = QString("%1 <span style='color:#dc3545;'>%2</span>: %3")
        .arg(timestamp, action, details);
    }
    else if (action == "DELETE") {
        entry = QString("%1 <span style='color:black;'>%2: %3</span>")
        .arg(timestamp, action, details);
    }
    else {
        // For SYSTEM messages, use black color
        entry = QString("%1 <span style='color:black;'>%2: %3</span>").arg(timestamp, action, details);
    }

    historyLog.prepend(entry);

    // Keep only the last 100 entries
    if (historyLog.size() > 100) {
        historyLog.removeLast();
    }
}
void MainWindow::on_pushButton_clicked()
{
    // Get all form values with validation

    QString FIRST_NAME = ui->lineEdit_2->text().trimmed();
    QString LAST_NAME = ui->lastnameln->text().trimmed();
    QString GENDER = ui->comboBox_2->currentText();
    QDate DATE_OF_BIRTH = ui->dateEdit_2->date();
    QString ADDRESS = ui->lineEdit_3->text().trimmed();
    QString EMAIL = ui->emailln->text();
    QString PHONE_NUMBER = ui->phoneln->text();

    // Validate required fields
    /*if (PATIENT_ID.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "PATIENT ID cannot be empty!");
        ui->lineEdit->setFocus();
        return;
    }
*/
    if (FIRST_NAME.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "First name cannot be empty!");
        ui->lineEdit_2->setFocus();
        return;
    }

    if (LAST_NAME.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Last name cannot be empty!");
        ui->lineEdit_3->setFocus();
        return;
    }
    if (ADDRESS.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Adress cannot be empty!");
        ui->lineEdit_3->setFocus();
        return;
    }
    QRegularExpression emailRegex(R"((^[\w.-]+@[\w.-]+\.[a-zA-Z]{2,}$))");
    if (!emailRegex.match(EMAIL).hasMatch()) {
        QMessageBox::warning(this, "Validation Error", "Invalid email format!,exp@gmail.com");
        ui->emailln->setFocus();
        return;
    }

    QRegularExpression phoneRegex(R"(^\+?\d{8,15}$)");
    if (!phoneRegex.match(PHONE_NUMBER).hasMatch()) {
        QMessageBox::warning(this, "Validation Error",
                             "Phone number must contain only digits (optionally starting with '+') and be 8 to 15 digits long.");
        ui->phoneln->setFocus();
        return;
    }
    // Create vaccine object
    Patient Patient(FIRST_NAME, LAST_NAME, GENDER, DATE_OF_BIRTH, ADDRESS, EMAIL, PHONE_NUMBER);
    // Handle Add/Modify mode
    if (currentEditRow >= 0) {
        // MODIFY EXISTING PATIENT
        QString patientId = ui->tableWidget->item(currentEditRow, 0)->text();

        if (!Patient.modifier(patientId)) {
            QMessageBox::warning(this, "Update Failed",
                                 "Failed to update patient in database.");
            return;
        }
        addHistoryEntry("MODIFY", QString("Updated patient %1 %2").arg(FIRST_NAME, LAST_NAME));
        currentEditRow = -1;
        ui->radioButton->setChecked(true);
        ui->pushButton->setText("Add");
        statusBar()->showMessage("Patient updated successfully", 3000);
    } else {
        // ADD NEW PATIENT
        if (!Patient.ajouter()) {
            QMessageBox::warning(this, "Add Failed",
                                 "Failed to add patient to database.");
            return;
        }
        addHistoryEntry("ADD", QString("Added new patient %1 %2").arg(LAST_NAME, FIRST_NAME));
        statusBar()->showMessage("Patient added successfully", 3000);
    }

    // Refresh the table and clear the form
    refreshTable();
    clearForm();

    // Update delete buttons (in case row numbers changed)
    updateDeleteButtons();
}
void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked) {
        ui->pushButton->setText("Modify");

        // Check if a row is selected for modification
        QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            currentEditRow = selected.first()->row();

            // Load data from selected row into form
            ui->lineEdit_2->setText(ui->tableWidget->item(currentEditRow, 1)->text());
            ui->lastnameln->setText(ui->tableWidget->item(currentEditRow, 2)->text());
            ui->comboBox_2->setCurrentText(ui->tableWidget->item(currentEditRow, 3)->text());
            ui->dateEdit_2->setDate(QDate::fromString(ui->tableWidget->item(currentEditRow, 4)->text(), "yyyy-MM-dd"));
            ui->lineEdit_3->setText(ui->tableWidget->item(currentEditRow, 5)->text());
            ui->emailln->setText(ui->tableWidget->item(currentEditRow, 6)->text());
            ui->phoneln->setText(ui->tableWidget->item(currentEditRow, 7)->text());
        } else {
            if(darkModeEnabled){            QMessageBox msgBox(this);
                msgBox.setWindowTitle("Information");
                msgBox.setText("Please select a row to modify");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setStyleSheet(
                    "QMessageBox {"
                    "   background-color: #white;"
                    "   border: 1px solid #dee2e6;"
                    "   border-radius: 5px;"
                    "}"
                    "QMessageBox QLabel {"
                    "   color: #white;"
                    "   font-size: 14px;"
                    "   padding: 10px;"
                    "}"
                    "QMessageBox QPushButton {"
                    "   background-color: #17a2b8;"
                    "   color: white;"
                    "   border-radius: 4px;"
                    "   padding: 5px 15px;"
                    "   min-width: 80px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "   background-color: #138496;"
                    "}"
                    "QMessageBox QPushButton:pressed {"
                    "   background-color: #0c636e;"
                    "}"
                    );
                msgBox.exec();
                ui->radioButton->setChecked(true); // Switch back to Add mode
                ui->pushButton->setText("Add");}
            // Before showing the message box, set its stylesheet
            else{
                QMessageBox msgBox(this);
                msgBox.setWindowTitle("Information");
                msgBox.setText("Please select a row to modify");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setStyleSheet(
                    "QMessageBox {"
                    "   background-color: #white;"
                    "   color:#white;                           "
                    "   border: 1px solid #dee2e6;"
                    "   border-radius: 5px;"
                    "}"
                    "QMessageBox QLabel {"
                    "   color: #212529;"
                    "   font-size: 14px;"
                    "   padding: 10px;"
                    "}"
                    "QMessageBox QPushButton {"
                    "   background-color: #17a2b8;"
                    "   color: white;"
                    "   border-radius: 4px;"
                    "   padding: 5px 15px;"
                    "   min-width: 80px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "   background-color: #138496;"
                    "}"
                    "QMessageBox QPushButton:pressed {"
                    "   background-color: #0c636e;"
                    "}"
                    );
                msgBox.exec();
                ui->radioButton->setChecked(true); // Switch back to Add mode
                ui->pushButton->setText("Add");}

        }
    }
}
void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked) {
        ui->pushButton->setText("Add");
        currentEditRow = -1; // Reset edit mode
        clearForm();
    }
}
// In mainwindow.cpp, modify the on_pushButton_8_clicked function:
void MainWindow::on_pushButton_8_clicked()
{
    const int dateColumn = 4; // Date of Birth column index

    QMap<QString, int> monthlyStats;
    int validDates = 0;

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* dateItem = ui->tableWidget->item(row, dateColumn);
        if (!dateItem || dateItem->text().isEmpty()) continue;

        QString rawDate = dateItem->text().trimmed();
        QDate date;

        // Essayons différents formats de date courants
        QStringList formats = {"yyyy-MM-dd", "dd/MM/yyyy", "dd-MM-yyyy", "dd-MMM-yyyy", "MMM dd yyyy"};

        for (const QString& format : formats) {
            date = QDate::fromString(rawDate, format);
            if (date.isValid()) {
                break;
            }
        }

        if (date.isValid()) {
            QString monthYear = date.toString("MMMM yyyy"); // Exemple : "May 2024"
            monthlyStats[monthYear]++;
            validDates++;
            qDebug() << "Valid date found:" << rawDate << "->" << monthYear;
        } else {
            qDebug() << "Invalid date format:" << rawDate;
        }
    }

    if (validDates == 0) {
        QMessageBox::information(this, "No Data", "No valid patient dates found");
        return;
    }

    StatsDialog *statsDialog = new StatsDialog(this);
    statsDialog->setMonthlyPatientData(monthlyStats);
    statsDialog->exec();
    delete statsDialog;
}

void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export PDF",
                                                    QDir::homePath() + "/patients_table.pdf",
                                                    "PDF Files (*.pdf)");

    if (!fileName.isEmpty()) {
        if (PDFExporter::exportToPDF(ui->tableWidget, "Patient Stock Report", fileName)) {
            QMessageBox::information(this, "Success", "Table exported to PDF successfully!");
            addHistoryEntry("EXPORT", "Exported table to PDF: " + fileName);
        } else {
            QMessageBox::warning(this, "Error", "Failed to export PDF. The table might be empty.");
        }
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    HistoryDialog *historyDialog = new HistoryDialog(this);
    historyDialog->setHistory(historyLog);

    connect(historyDialog, &HistoryDialog::historyCleared, this, [this]() {
        historyLog.clear();
        // Add clean history entry without HTML formatting
        QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]");
        historyLog.prepend(timestamp + " SYSTEM: History log was cleared");
    });

    historyDialog->exec();
    delete historyDialog;
}

// Helper function to show styled alerts
void MainWindow::showStyledAlert(const QString &title, const QString &message,
                                 QMessageBox::Icon icon, const QString &buttonColor)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setIcon(icon);
    msgBox.setTextFormat(Qt::RichText);

    msgBox.setStyleSheet(
        QString(
            "QMessageBox {"
            "   background-color: #white;"
            "   font-family: Arial;"
            "}"
            "QMessageBox QLabel {"
            "   color: #144976;"
            "   font-size: 12pt;"
            "}"
            "QMessageBox QPushButton {"
            "   background-color: %1;"
            "   color: #white;"
            "   padding: 8px 16px;"
            "   border-radius: 4px;"
            "   min-width: 80px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "   background-color: %2;"
            "}"
            ).arg(buttonColor, QColor(buttonColor).darker(110).name())
        );

    msgBox.setText(message);
    msgBox.exec();
}

void MainWindow::on_pushButton_10_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime warningThreshold = currentDateTime.addDays(2);

    // Ajuste les heures
    QDateTime startDate = QDateTime(currentDateTime.date(), QTime(0, 0, 0));
    QDateTime endDate = QDateTime(warningThreshold.date(), QTime(23, 59, 59));

    bool foundUpcomingAppointments = false;
    QStringList upcomingAppointments;

    QSqlQuery query;
    query.prepare("SELECT patient_id, appointment_date, appointment_time, purpose "
                  "FROM appointments "
                  "WHERE appointment_date BETWEEN TO_TIMESTAMP(:now, 'YYYY-MM-DD HH24:MI:SS') "
                  "AND TO_TIMESTAMP(:threshold, 'YYYY-MM-DD HH24:MI:SS') "
                  "ORDER BY appointment_date, appointment_time");

    query.bindValue(":now", startDate.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":threshold", endDate.toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        qWarning() << "Failed to query appointments:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        foundUpcomingAppointments = true;
        QString patientId = query.value("patient_id").toString();
        QDateTime apptDateTime = query.value("appointment_date").toDateTime();
        QString purpose = query.value("purpose").toString();

        qint64 hoursUntil = currentDateTime.secsTo(apptDateTime) / 3600;

        upcomingAppointments.append(
            QString("<tr><td style='padding:5px;'>• <b>%1</b></td>"
                    "<td style='padding:5px;'>Patient %2</td>"
                    "<td style='padding:5px;'>%3</td>"
                    "<td style='padding:5px; color:blue;'>in %4 hours</td></tr>")
                .arg(apptDateTime.toString("MMM d hh:mm AP"),
                     patientId,
                     purpose,
                     QString::number(hoursUntil))
            );
    }

    if (foundUpcomingAppointments) {
        QString html = QString(
                           "<html><body style='font-family:Arial; font-size:12pt;'>"
                           "<h3 style='color:#17a2b8;'>⚠ Upcoming Appointments</h3>"
                           "<p>These appointments are coming soon:</p>"
                           "<table style='width:100%; border-collapse:collapse;'>%1</table>"
                           "</body></html>"
                           ).arg(upcomingAppointments.join(""));

        showStyledAlert("Appointment Alerts", html, QMessageBox::Information, "#17a2b8");
    } else {
        showStyledAlert("Appointments",
                        "<h3 style='color:#28a745;'>✓ No Upcoming Appointments</h3>"
                        "<p>No appointments in the next 2 days.</p>",
                        QMessageBox::Information, "#28a745");
    }
}

void MainWindow::onDeleteButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    if (row < 0 || row >= ui->tableWidget->rowCount()) return;

    // Get the patient ID from the first column
    QString patientid = ui->tableWidget->item(row, 0)->text();

    // Create and style the confirmation dialog
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle("Confirm Delete");
    confirmBox.setText(QString("Are you sure you want to delete patient %1?").arg(patientid));
    confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmBox.setDefaultButton(QMessageBox::No);
    confirmBox.setIcon(QMessageBox::Question);

    // Apply styling based on dark mode
    QString styleSheet;
    if(darkModeEnabled) {
        styleSheet =
            "QMessageBox {"
            "   background-color: #343a40;"
            "   border: 1px solid #495057;"
            "}"
            "QMessageBox QLabel {"
            "   color: #f8f9fa;"
            "   font-size: 14px;"
            "   padding: 10px;"
            "}"
            "QMessageBox QPushButton {"
            "   min-width: 80px;"
            "   padding: 5px 15px;"
            "   border-radius: 4px;"
            "}"
            "QMessageBox QPushButton[text=\"Yes\"] {"
            "   background-color: #dc3545;"
            "   color: white;"
            "}"
            "QMessageBox QPushButton[text=\"No\"] {"
            "   background-color: #6c757d;"
            "   color: white;"
            "}"
            "QMessageBox QPushButton:hover {"
            "   background-color: #c82333;"
            "}"
            "QMessageBox QPushButton[text=\"No\"]:hover {"
            "   background-color: #5a6268;"
            "}";
    } else {
        styleSheet =
            "QMessageBox {"
            "   background-color: #f8f9fa;"
            "   border: 1px solid #dee2e6;"
            "   border-radius: 5px;"
            "}"
            "QMessageBox QLabel {"
            "   background-color: #f8f9fa;"
            "   color: #212529;"
            "   font-size: 14px;"
            "   padding: 10px;"
            "}"
            "QMessageBox QPushButton {"
            "   min-width: 80px;"
            "   padding: 5px 15px;"
            "   border-radius: 4px;"
            "}"
            "QMessageBox QPushButton[text=\"Yes\"] {"
            "   background-color: #f8f9fa;"
            "   color: white;"
            "}"
            "QMessageBox QPushButton[text=\"No\"] {"
            "   background-color: #f8f9fa;"
            "   color: white;"
            "}"
            "QMessageBox QPushButton:hover {"
            "   background-color: #c82333;"
            "}"
            "QMessageBox QPushButton[text=\"No\"]:hover {"
            "   background-color: #5a6268;"
            "}";
    }

    confirmBox.setStyleSheet(styleSheet);
    QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(confirmBox.exec());

    if (reply == QMessageBox::Yes) {
        if (Patient::supprimer(patientid)) {
            // Remove from table if database deletion succeeded
            ui->tableWidget->removeRow(row);
            statusBar()->showMessage(QString("Patient %1 deleted successfully").arg(patientid), 3000);

            // Update row properties for remaining buttons
            updateDeleteButtons();

            // Add to history log
            addHistoryEntry("DELETE", QString("Deleted patient ID %1").arg(patientid));
        } else {
            QMessageBox::warning(this, "Delete Failed",
                                 QString("Failed to delete patient %1").arg(patientid));
        }
    }
}
void MainWindow::updateDeleteButtons()
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QWidget* widget = ui->tableWidget->cellWidget(row, 8);
        if (widget) {
            widget->setProperty("row", row);
        }
    }
}
void MainWindow::onModifyButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    if (row < 0 || row >= ui->tableWidget->rowCount()) return;

    // Switch to modify mode
    ui->radioButton_2->setChecked(true);

    // This will trigger the existing modify logic in on_radioButton_2_toggled
    // Select the row to ensure the data is loaded into the form
    ui->tableWidget->selectRow(row);
}
void MainWindow::onSortComboBoxChanged(int index)
{
    if (ui->tableWidget->rowCount() == 0) return;
    QString sortBy = ui->comboBox_4->currentText();

    // Disable sorting while we prepare the data
    ui->tableWidget->setSortingEnabled(false);

    if (sortBy == "Patient ID") {
        ui->tableWidget->sortItems(1, Qt::AscendingOrder);
    }
    else if (sortBy == "First name") {
        // For date columns, we need to ensure proper sorting
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, 1);
            if (item) {
                QDate date = QDate::fromString(item->text(), "yyyy-MM-dd");
                item->setData(Qt::UserRole, date);
            }
        }
        ui->tableWidget->sortItems(3, Qt::AscendingOrder);
    }
    else if (sortBy == "AGE") {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, 4);
            if (item) {
                QDate date = QDate::fromString(item->text(), "yyyy-MM-dd");
                item->setData(Qt::UserRole, date);
            }
        }
        ui->tableWidget->sortItems(4, Qt::AscendingOrder);
    }
    else if (sortBy == "Gender") {
        // No special processing needed — just sort the text directly
        ui->tableWidget->sortItems(3, Qt::AscendingOrder); // Column 3 is Gender
    }


    // Re-enable sorting
    ui->tableWidget->setSortingEnabled(true);
}
void MainWindow::on_searchButton_clicked()
{
    // Get the search text and selected column
    QString searchText = ui->lineEdit_4->text().trimmed();
    QString searchBy = ui->comboBox_3->currentText();

    // If no specific search criteria selected or empty search text, show all rows
    if (searchBy == "search by" || searchText.isEmpty()) {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            ui->tableWidget->setRowHidden(row, false);
        }
        statusBar()->showMessage("Showing all records", 2000);
        return;
    }

    // Determine which column to search in
    int column = -1;
    if (searchBy == "Patient ID") column = 0;
    else if (searchBy == "First name") column = 1;
    else if (searchBy == "Last name") column = 2;
    else if (searchBy == "Gender") column = 3;
    else if (searchBy == "Date of birth") column = 4;
    else if (searchBy == "Adress") column = 5;
    else if (searchBy == "Email") column = 6;
    else if (searchBy == "Phone number") column = 7;

    // If valid column selected, perform the search
    if (column != -1) {
        int matchesFound = 0;

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            bool shouldShow = false;

            if (item) {
                QString itemText = item->text();

                // Special handling for numeric columns (Stock Quantity)
                if (column == 7) {
                    bool ok1, ok2;
                    int itemValue = itemText.toInt(&ok1);
                    int searchValue = searchText.toInt(&ok2);
                    if (ok1 && ok2) {
                        shouldShow = (itemValue == searchValue);
                    } else {
                        // Fallback to text search if conversion fails
                        shouldShow = itemText.contains(searchText, Qt::CaseInsensitive);
                    }
                }
                // Special handling for date columns
                else if (column == 3 || column == 4) {
                    QDate itemDate = QDate::fromString(itemText, "yyyy-MM-dd");
                    QDate searchDate = QDate::fromString(searchText, "yyyy-MM-dd");
                    if (itemDate.isValid() && searchDate.isValid()) {
                        shouldShow = (itemDate == searchDate);
                    } else {
                        // Fallback to text search if date parsing fails
                        shouldShow = itemText.contains(searchText, Qt::CaseInsensitive);
                    }
                }
                // Default text search for other columns
                else {
                    shouldShow = itemText.contains(searchText, Qt::CaseInsensitive);
                }
            }

            ui->tableWidget->setRowHidden(row, !shouldShow);
            if (shouldShow) matchesFound++;
        }

        // Show search results summary
        if (matchesFound > 0) {
            statusBar()->showMessage(QString("Found %1 matching records").arg(matchesFound), 3000);
        } else {
            statusBar()->showMessage("No matching records found", 3000);
        }
    } else {
        statusBar()->showMessage("Please select a valid search criteria", 3000);
    }
}

void MainWindow::filterTable(const QString &searchText, int column)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *item = ui->tableWidget->item(row, column);
        bool match = matchesSearch(item, searchText);
        ui->tableWidget->setRowHidden(row, !match);
    }
}
bool MainWindow::matchesSearch(const QTableWidgetItem *item, const QString &searchText)
{
    if (!item) return false;

    // Special handling for numeric columns (Stock Quantity)
    if (item->column() == 7) {
        bool ok;
        int stock = item->text().toInt(&ok);
        int searchValue = searchText.toInt(&ok);
        if (ok) {
            return stock == searchValue;
        }
        return false;
    }
    // Special handling for date columns
    else if (item->column() == 3 || item->column() == 4) {
        QDate itemDate = QDate::fromString(item->text(), "yyyy-MM-dd");
        QDate searchDate = QDate::fromString(searchText, "yyyy-MM-dd");
        if (itemDate.isValid() && searchDate.isValid()) {
            return itemDate == searchDate;
        }
        return false;
    }

    // Default text comparison (case insensitive)
    return item->text().contains(searchText, Qt::CaseInsensitive);
}
void MainWindow::toggleDarkMode(bool enabled)
{
    if (enabled) {
        // Dark mode styles - customize these to match your design
        QString darkStyle =
            "QMainWindow { background-color: #2d2d2d; }"
            "QTableWidget { background-color: 353535; color: #ffffff; "
            "               gridline-color: #555555; alternate-background-color: #353535;}"
            "QTableWidget QHeaderView::section { background-color: #252525; "
            "                                    color: #ffffff; }"
            "QGroupBox { background-color: transparent; color: #ffffff; "
            "            border: 1px solid #555555; }"
            "QLineEdit, QComboBox, QDateEdit, QSpinBox {"
            "    background-color: #454545; color: #black; "
            "    border: 1px solid #555555; }"
            "QPushButton { background-color: transparent; color: #ffffff; }"
            "QPushButton:hover { background-color: #606060; }"
            "QRadioButton { color: #ffffff; }"
            "QLabel { color: #ffffff; }"
            "QHeaderView::section { background-color: #252525; color: white; }";

        this->setStyleSheet(darkStyle);
        ui->pushButton_9->setIcon(QIcon("C:/Users/Firas/OneDrive/Desktop/QT/VaxEra/darkmodetest/images/sombre.png"));
    } else {
        // Restore original styles (from your .ui file)
        this->setStyleSheet(originalStyleSheet);
        ui->pushButton_9->setIcon(QIcon("C:/Users/Firas/OneDrive/Desktop/QT/VaxEra/darkmodetest/images/sombre.png"));
    }

    // Update the button tooltip
    ui->pushButton_9->setToolTip(enabled ? "Switch to Light Mode" : "Switch to Dark Mode");
}
void MainWindow::onAddAppointmentClicked()
{
    qDebug() << "Add Appointment clicked";
    QMessageBox::information(this, "Debug", "Add button works");

    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a patient first.");
        return;
    }

    QString patientId = ui->tableWidget->item(selected.first()->row(), 0)->text();

    QDialog dialog(this);
    QFormLayout form(&dialog);

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), &dialog);
    QLineEdit *purposeEdit = new QLineEdit(&dialog);
    QTextEdit *notesEdit = new QTextEdit(&dialog);

    form.addRow("Date & Time:", dateTimeEdit);
    form.addRow("Purpose:", purposeEdit);
    form.addRow("Notes:", notesEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QSqlQuery query;
        QDateTime selectedDateTime = dateTimeEdit->dateTime();

        QString timestampStr = selectedDateTime.toString("yyyy-MM-dd HH:mm:ss");  // Define this!

        query.prepare("INSERT INTO appointments (patient_id, appointment_date, purpose, notes) "
                      "VALUES (:pid, TO_TIMESTAMP(:ts, 'YYYY-MM-DD HH24:MI:SS'), :purpose, :notes)");

        query.bindValue(":pid", patientId);
        query.bindValue(":ts", timestampStr);
        query.bindValue(":purpose", purposeEdit->text());
        query.bindValue(":notes", notesEdit->toPlainText());

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to save appointment: " + query.lastError().text());
        } else {
            loadAppointmentsForPatient(patientId);
            addHistoryEntry("APPOINTMENT", QString("Added appointment for patient %1").arg(patientId));
        }
    }
}


void MainWindow::onViewAppointmentsClicked()
{
    qDebug() << "View Appointments clicked";
    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a patient first.");
        return;
    }

    QString patientId = ui->tableWidget->item(selected.first()->row(), 0)->text();
    loadAppointmentsForPatient(patientId);

    // Show appointments in a dialog
    QDialog dialog(this);
    dialog.setWindowTitle(QString("Appointments for Patient %1").arg(patientId));
    dialog.resize(800, 400);  // Wider dialog to accommodate all columns
    QVBoxLayout layout(&dialog);

    QTableWidget *appointmentsTable = new QTableWidget(&dialog);
    appointmentsTable->setColumnCount(6);  // Changed from 5 to 6 columns
    appointmentsTable->setHorizontalHeaderLabels({"ID", "Date", "Time", "Purpose", "Status", "Notes"});
    appointmentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // Auto-resize columns

    const auto appointments = appointmentsData.value(patientId);
    appointmentsTable->setRowCount(appointments.size());

    for (int i = 0; i < appointments.size(); ++i) {
        const auto &appt = appointments[i];
        // Add ID in first column
        appointmentsTable->setItem(i, 0, new QTableWidgetItem(appt["id"].toString()));
        appointmentsTable->setItem(i, 1, new QTableWidgetItem(appt["appointment_date"].toString()));
        appointmentsTable->setItem(i, 2, new QTableWidgetItem(appt["appointment_time"].toString()));
        appointmentsTable->setItem(i, 3, new QTableWidgetItem(appt["purpose"].toString()));
        appointmentsTable->setItem(i, 4, new QTableWidgetItem(appt["status"].toString()));
        appointmentsTable->setItem(i, 5, new QTableWidgetItem(appt["notes"].toString()));
    }

    // Make the table read-only
    appointmentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout.addWidget(appointmentsTable);
    dialog.exec();
}

void MainWindow::loadAppointmentsForPatient(const QString &patientId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM appointments WHERE patient_id = ? ORDER BY appointment_date, appointment_time");
    query.addBindValue(patientId);

    if (!query.exec()) {
        qWarning() << "Failed to load appointments:" << query.lastError().text();
        return;
    }

    QList<QVariantMap> appointments;
    while (query.next()) {
        QVariantMap appt;
        appt["id"] = query.value("id");
        appt["appointment_date"] = query.value("appointment_date");
        appt["appointment_time"] = query.value("appointment_time");
        appt["purpose"] = query.value("purpose");
        appt["status"] = query.value("status");
        appt["notes"] = query.value("notes");
        appointments.append(appt);
    }

    appointmentsData[patientId] = appointments;
}
// In constructor:
MainWindow::~MainWindow()
{
    delete ui;
}
