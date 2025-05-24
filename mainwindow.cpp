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
#include<QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentEditRow(-1)
{

    ui->setupUi(this);
    QTimer::singleShot(0, this, [this]() {
            loadVaccinesFromDatabase();
        });
    //initializeTable();
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("sort by");
    ui->comboBox_4->addItem("Vaccine Name");
    ui->comboBox_4->addItem("Manufacturing Date");
    ui->comboBox_4->addItem("Expiration Date");
    ui->comboBox_4->addItem("Stock Quantity");

    // Initialize table columns - add "Action" column for delete button
    QStringList headers = {"ID Vaccine", "Vaccine Name", "Type",
                           "Manufacturing Date", "Expiration Date",
                           "Batch Number", "Supplier", "Stock Quantity", "Action"}; // Added "Action"
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Set column widths
    ui->tableWidget->setColumnWidth(0, 140); // ID Vaccine
    ui->tableWidget->setColumnWidth(1, 130); // Vaccine Name
    ui->tableWidget->setColumnWidth(2, 110); // Type
    ui->tableWidget->setColumnWidth(3, 160); // Manufacturing Date
    ui->tableWidget->setColumnWidth(4, 160); // Expiration Date
    ui->tableWidget->setColumnWidth(5, 120); // Batch Number
    ui->tableWidget->setColumnWidth(6, 120); // Supplier
    ui->tableWidget->setColumnWidth(7, 130); // Stock Quantity
    ui->tableWidget->setColumnWidth(8, 100); // Action column for delete button
    // For text columns (like Vaccine Name), you might want case-insensitive sorting
    ui->tableWidget->setSortingEnabled(true);

    // Set header height
    ui->tableWidget->horizontalHeader()->setFixedHeight(40);

    // Initialize combo boxes
    ui->comboBox->addItems({"Primary", "Booster"});
    ui->comboBox_2->addItems({"Sanofi Pasteur", "Novavax", "GlaxoSmithKline", "Moderna", "AstraZeneca"});
    connect(ui->comboBox_4, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSortComboBoxChanged);

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
    // Get data using the afficher() method
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM vaccine");

    if (model->lastError().isValid()) {
        qCritical() << "Failed to load vaccines:" << model->lastError().text();
        delete model;
        return;
    }

    // Populate the table
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidget->setItem(row, col, item);
        }

        // Add delete button
        QPushButton *deleteButton = new QPushButton("Delete");
        deleteButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #dc3545;"
            "   color: white;"
            "   padding: 5px;"
            "   border-radius: 4px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #c82333;"
            "}"
            );
        deleteButton->setProperty("row", row);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
        ui->tableWidget->setCellWidget(row, 8, deleteButton);
    }

    delete model;
}

void MainWindow::refreshTable()
{
    loadVaccinesFromDatabase();
}

void MainWindow::clearForm()
{
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate(2025, 1, 1));
    ui->dateEdit_2->setDate(QDate(2025, 1, 1));
    ui->lineEdit_3->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->spinBox->setValue(0);
}


void MainWindow::addHistoryEntry(const QString &action, const QString &details)
{
    QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]");
    QString entry;

    // Color code different types of entries
    if (action == "ADD") {
        entry = QString("%1  %3")
        .arg(timestamp, details);
    }
    else if (action == "MODIFY") {
        entry = QString("%1 %3")
        .arg(timestamp, details);
    }
    else if (action == "DELETE") {
        entry = QString("%1 %3")
        .arg(timestamp, details);
    }
    else if (action == "EXPIRED" || action == "OUT OF STOCK") {
        entry = QString("%1 %3").arg(timestamp, details);
    }
    else {
        // For SYSTEM messages, don't use HTML formatting
        entry = QString("%1 %2: %3").arg(timestamp, action, details);
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
    QString name = ui->lineEdit_2->text().trimmed();
    QString type = ui->comboBox->currentText();
    QDate manuDate = ui->dateEdit->date();
    QDate expDate = ui->dateEdit_2->date();
    QString batch = ui->lineEdit_3->text().trimmed();
    QString supplier = ui->comboBox_2->currentText();
    int stock = ui->spinBox->value();

    /* Validate required fields
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Vaccine ID cannot be empty!");
        ui->lineEdit->setFocus();
        return;
    }*/
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Vaccine name cannot be empty!");
        ui->lineEdit_2->setFocus();
        return;
    }
    if (batch.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Batch number cannot be empty!");
        ui->lineEdit_3->setFocus();
        return;
    }
    // Validate dates
    if (manuDate >= expDate) {
        QMessageBox::warning(this, "Validation Error",
                             "Expiration date must be after manufacturing date!");
        ui->dateEdit_2->setFocus();
        return;
    }

    // Validate stock quantity
    if (stock < 0) {
        QMessageBox::warning(this, "Validation Error", "Stock quantity cannot be negative!");
        ui->spinBox->setFocus();
        return;
    }

    // Create vaccine object
    Vaccine vaccine(name, type, manuDate, expDate, batch, supplier, stock);

    // Handle Add/Modify mode
    if (currentEditRow >= 0) {
        // MODIFY EXISTING VACCINE
        QString vacid =ui->tableWidget->item(currentEditRow,0)->text();
        if (!vaccine.modifier(vacid)){
            QMessageBox::warning(this, "Update Failed",
                                 QString("Failed to update vaccine %1 in database.").arg(vacid));
            return;
        }

        // Log the modification
        addHistoryEntry("MODIFY", QString("Updated vaccine ID %1 (%2)").arg(vacid, name));

        // Reset edit mode
        currentEditRow = -1;
        ui->radioButton->setChecked(true);
        ui->pushButton->setText("Add");

        statusBar()->showMessage(QString("Vaccine %1 updated successfully").arg(vacid), 3000);
    } else {

        // ADD NEW VACCINE
        if (!vaccine.ajouter()) {
            QMessageBox::warning(this, "Add Failed",
                                 QString("Failed to add vaccine  to database."));
            return;
        }

        // Log the addition
        addHistoryEntry("ADD", QString("Added new vaccine ID  (%2)").arg(name));

        statusBar()->showMessage(QString("Vaccine added successfully"), 3000);
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
            ui->comboBox->setCurrentText(ui->tableWidget->item(currentEditRow, 2)->text());
            ui->dateEdit->setDate(QDate::fromString(ui->tableWidget->item(currentEditRow, 3)->text(), "yyyy-MM-dd"));
            ui->dateEdit_2->setDate(QDate::fromString(ui->tableWidget->item(currentEditRow, 4)->text(), "yyyy-MM-dd"));
            ui->lineEdit_3->setText(ui->tableWidget->item(currentEditRow, 5)->text());
            ui->comboBox_2->setCurrentText(ui->tableWidget->item(currentEditRow, 6)->text());
            ui->spinBox->setValue(ui->tableWidget->item(currentEditRow, 7)->text().toInt());
        } else {
            QMessageBox::information(this, "Information", "Please select a row to modify");
            ui->radioButton->setChecked(true); // Switch back to Add mode
            ui->pushButton->setText("Add");

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

void MainWindow::on_pushButton_8_clicked()
{
    // Collect vaccine stock data from the table
    QMap<QString, int> vaccineData;

    for(int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* nameItem = ui->tableWidget->item(row, 1); // Column 1: Vaccine Name
        QTableWidgetItem* stockItem = ui->tableWidget->item(row, 7); // Column 7: Stock Quantity

        if(nameItem && stockItem) {
            QString vaccineName = nameItem->text();
            bool ok;
            int stock = stockItem->text().toInt(&ok);

            if(ok) {
                // Sum stocks if same vaccine appears multiple times
                vaccineData[vaccineName] += stock;
            }
        }
    }

    // Create and show statistics dialog if we have data
    if(!vaccineData.isEmpty()) {
        StatsDialog *statsDialog = new StatsDialog(this);
        statsDialog->setData(vaccineData);
        statsDialog->exec();
        delete statsDialog;
    } else {
        QMessageBox::information(this, "No Data", "No vaccine data available to display statistics.");
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export PDF",
                                                    QDir::homePath() + "/vaccine_table.pdf",
                                                    "PDF Files (*.pdf)");

    if (!fileName.isEmpty()) {
        if (PDFExporter::exportToPDF(ui->tableWidget, "Vaccine Stock Report", fileName)) {
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
    loadVaccinesFromDatabase();

    if (ui->tableWidget->rowCount() == 0) {
        showStyledAlert("No Vaccines", "There are no vaccines in the inventory.",
                        QMessageBox::Information, "#6c757d");
        return;
    }

    QDate currentDate = QDate::currentDate();
    qDebug() << "Current date:" << currentDate.toString("yyyy-MM-dd");

    bool foundExpired = false;
    bool foundOutOfStock = false;
    QStringList expiredVaccines;
    QStringList outOfStockVaccines;

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* idItem = ui->tableWidget->item(row, 0);
        QTableWidgetItem* nameItem = ui->tableWidget->item(row, 1);
        QTableWidgetItem* expDateItem = ui->tableWidget->item(row, 4);
        QTableWidgetItem* stockItem = ui->tableWidget->item(row, 7);

        if (!idItem || !nameItem || !expDateItem || !stockItem) {
            continue;
        }

        QString id = idItem->text();
        QString name = nameItem->text();
        QString expDateStr = expDateItem->text();
        QString stockStr = stockItem->text();

        // Parse expiration date (handle ISO format with time)
        QDate expDate = QDate::fromString(expDateStr.left(10), "yyyy-MM-dd");
        if (!expDate.isValid()) {
            qWarning() << "Invalid date for vaccine" << id << ":" << expDateStr;
            continue;
        }

        // Parse stock quantity
        bool ok;
        int stock = stockStr.toInt(&ok);
        if (!ok) {
            qWarning() << "Invalid stock for vaccine" << id << ":" << stockStr;
            continue;
        }

        // Check expiration
        if (expDate < currentDate) {
            foundExpired = true;
            QString entry = QString("<tr><td style='padding: 5px;'>• <b>%1</b></td>"
                                    "<td style='padding: 5px;'>%2</td>"
                                    "<td style='padding: 5px; color: red;'>Expired on %3</td></tr>")
                                .arg(id).arg(name).arg(expDate.toString("MMM d, yyyy"));
            expiredVaccines.append(entry);
        }

        // Check stock
        if (stock <= 0) {
            foundOutOfStock = true;
            QString entry = QString("<tr><td style='padding: 5px;'>• <b>%1</b></td>"
                                    "<td style='padding: 5px;'>%2</td>"
                                    "<td style='padding: 5px; color: orange;'>Out of stock</td></tr>")
                                .arg(id).arg(name);
            outOfStockVaccines.append(entry);
        }
    }

    if (foundExpired || foundOutOfStock) {
        QString html = "<html><body style='font-family: Arial; font-size: 12pt;'>";

        if (foundExpired) {
            html += QString("<div style='margin-bottom: 20px;'>"
                            "<h3 style='color: #dc3545;'>⚠️ Expired Vaccines</h3>"
                            "<table style='width: 100%;'>%1</table></div>")
                        .arg(expiredVaccines.join(""));
        }

        if (foundOutOfStock) {
            html += QString("<div style='margin-bottom: 20px;'>"
                            "<h3 style='color: #fd7e14;'>⚠️ Out of Stock</h3>"
                            "<table style='width: 100%;'>%1</table></div>")
                        .arg(outOfStockVaccines.join(""));
        }

        html += "</body></html>";
        showStyledAlert("Vaccine Alerts", html, QMessageBox::Warning, "#144976");
    } else {
        showStyledAlert("Vaccine Status",
                        "<h3 style='color:#28a745;'>✓ All Good</h3>"
                        "<p>No expired or out-of-stock vaccines found.</p>",
                        QMessageBox::Information, "#28a745");
    }
}
void MainWindow::onDeleteButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    if (row < 0 || row >= ui->tableWidget->rowCount()) return;

    // Get the vaccine ID from the first column
    QString vaccineId = ui->tableWidget->item(row, 0)->text();

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  QString("Are you sure you want to delete vaccine %1?").arg(vaccineId),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Use the supprimer function from Vaccine class
        Vaccine vaccine;
        if (vaccine.supprimer(vaccineId)) {
            // Remove from table if database deletion succeeded
            ui->tableWidget->removeRow(row);
            statusBar()->showMessage(QString("Vaccine ID %1 deleted successfully").arg(vaccineId), 3000);
            addHistoryEntry("DELETE", QString("Deleted  vaccine ID  (%2)").arg(vaccineId));

            // Update row properties for remaining buttons
            updateDeleteButtons();
        } else {
            QMessageBox::warning(this, "Delete Failed",
                                 QString("Failed to delete vaccine %1").arg(vaccineId));
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
void MainWindow::onSortComboBoxChanged(int index)
{
    if (ui->tableWidget->rowCount() == 0) return;

    QString sortBy = ui->comboBox_4->currentText();

    // Disable sorting while we prepare the data
    ui->tableWidget->setSortingEnabled(false);

    if (sortBy == "Vaccine Name") {
        ui->tableWidget->sortItems(1, Qt::AscendingOrder);
    }
    else if (sortBy == "Manufacturing Date") {
        // For date columns, we need to ensure proper sorting
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, 3);
            if (item) {
                QDate date = QDate::fromString(item->text(), "yyyy-MM-dd");
                item->setData(Qt::UserRole, date);
            }
        }
        ui->tableWidget->sortItems(3, Qt::AscendingOrder);
    }
    else if (sortBy == "Expiration Date") {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, 4);
            if (item) {
                QDate date = QDate::fromString(item->text(), "yyyy-MM-dd");
                item->setData(Qt::UserRole, date);
            }
        }
        ui->tableWidget->sortItems(4, Qt::AscendingOrder);
    }
    else if (sortBy == "Stock Quantity") {
        // For numeric sorting
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, 7);
            if (item) {
                bool ok;
                int quantity = item->text().toInt(&ok);
                if (ok) {
                    item->setData(Qt::UserRole, quantity);
                }
            }
        }
        ui->tableWidget->sortItems(7, Qt::AscendingOrder);
    }

    // Re-enable sorting
    ui->tableWidget->setSortingEnabled(true);
}
bool MainWindow::dateLessThan(const QString &date1, const QString &date2)
{
    QDate d1 = QDate::fromString(date1, "yyyy-MM-dd");
    QDate d2 = QDate::fromString(date2, "yyyy-MM-dd");
    return d1 < d2;
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
    if (searchBy == "ID Vaccine") column = 0;
    else if (searchBy == "Vaccine Name") column = 1;
    else if (searchBy == "Type") column = 2;
    else if (searchBy == "Manufacturing Date") column = 3;
    else if (searchBy == "Expiration Date") column = 4;
    else if (searchBy == "Batch Number") column = 5;
    else if (searchBy == "Supplier") column = 6;
    else if (searchBy == "Stock Quantity") column = 7;

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
            "QTableWidget { background-color: #353535; color: #ffffff; "
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
            "QHeaderView::section { background-color: #252525; color: white; }";

        this->setStyleSheet(darkStyle);
        ui->pushButton_9->setIcon(QIcon("D:/MP2-IN/Qt creator/interface/darkmodetest/images/soleil.png"));
        ui->label_8->setPixmap(QPixmap("D:/MP2-IN/Qt creator/interface/darkmodetest/images/p2.png"));

    } else {
        // Restore original styles (from your .ui file)
        this->setStyleSheet(originalStyleSheet);
        ui->pushButton_9->setIcon(QIcon("D:/MP2-IN/Qt creator/interface/darkmodetest/images/sombre.png"));
        ui->label_8->setPixmap(QPixmap("D:/MP2-IN/Qt creator/interface/darkmodetest/images/p1.png"));

    }

    // Update the button tooltip
    ui->pushButton_9->setToolTip(enabled ? "Switch to Light Mode" : "Switch to Dark Mode");
}
MainWindow::~MainWindow()
{
    delete ui;
}
