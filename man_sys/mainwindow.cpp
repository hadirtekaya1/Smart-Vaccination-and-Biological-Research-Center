#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QDate>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlError>
#include <QDebug>
#include <QTimer>
#include <QLineEdit>
#include <QSqlQuery>
#include <QComboBox>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QTableView>
#include <QStackedWidget>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QTextDocument>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLegend>
#include <QPainter>
#include <QtCharts/QLegendMarker>
#include <QFont>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_mainModel(nullptr)
    , m_updateModel(nullptr)
    , m_deleteModel(nullptr)
{
    ui->setupUi(this);

    if (!DatabaseManager::instance().connectToDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the Oracle database.");
    } else {
        qDebug() << "Database connection successful on startup.";
    }

    setupNavigationAndConnections();

    if (ui->equipType_3) {
        onAddConsumableChanged(ui->equipType_3->currentText());
    }
    if (ui->equipConsum) {
        onUpdateConsumableChanged(ui->equipConsum->currentText());
    }

    if (ui->stackedWidget->currentWidget() == ui->searchWidget) {
        loadEquipmentTable();
        updateDashboardCounts();
    }

}

MainWindow::~MainWindow()
{
    delete m_mainModel;
    delete m_updateModel;
    delete m_deleteModel;
    delete ui;
}

void MainWindow::setupNavigationAndConnections()
{
    connect(ui->searchButton, &QPushButton::clicked, this, [this, ui=this->ui](){
        ui->stackedWidget->setCurrentWidget(ui->searchWidget);
    });
    connect(ui->addEquipButton, &QPushButton::clicked, this, [this, ui=this->ui](){
        ui->stackedWidget->setCurrentWidget(ui->equipAdd);
        if (ui->equipType_3) onAddConsumableChanged(ui->equipType_3->currentText());
    });
    connect(ui->updateEquipButton, &QPushButton::clicked, this, [this, ui=this->ui](){
        ui->stackedWidget->setCurrentWidget(ui->equipUpdate);
        loadUpdateEquipmentTable();
        ui->searchTextBox_3->clear();
        m_selectedUpdateId.clear();
        if(ui->equipName_3) ui->equipName_3->clear();
        if(ui->equipQuantity_2) ui->equipQuantity_2->clear();
        if(ui->equipPrice_2) ui->equipPrice_2->clear();
        if(ui->equipConsum) onUpdateConsumableChanged(ui->equipConsum->currentText());
    });
    connect(ui->deleteEquipButton, &QPushButton::clicked, this, [this, ui=this->ui](){
        ui->stackedWidget->setCurrentWidget(ui->equipDelete);
        loadDeleteEquipmentTable();
        ui->searchTextBox_2->clear();
    });
    connect(ui->goBack_5, &QPushButton::clicked, this, [this, ui=this->ui](){
        ui->stackedWidget->setCurrentWidget(ui->Home);
    });
    connect(ui->aboutButton, &QPushButton::clicked, this, [this, ui=this->ui](){
        ui->stackedWidget->setCurrentWidget(ui->about);
    });

    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [this, ui=this->ui]() {
        if (ui->stackedWidget->currentWidget() == ui->searchWidget) {
            loadEquipmentTable();
            updateDashboardCounts();
            ui->searchTextBox->clear();
        }
    });

    connect(ui->deleteEquipButton_2, &QPushButton::clicked, this, &MainWindow::on_deleteEquipButton_2_clicked);

    connect(ui->searchTextBox, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->searchTextBox_3, &QLineEdit::textChanged, this, &MainWindow::onUpdateSearchTextChanged);
    connect(ui->searchTextBox_2, &QLineEdit::textChanged, this, &MainWindow::on_searchTextBox_2_textChanged);
    connect(ui->satistics, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->statsPage);
        showStatsChart();
    });

    if(ui->equipType_3) {
        connect(ui->equipType_3, &QComboBox::currentTextChanged, this, &MainWindow::onAddConsumableChanged);
    }
    if(ui->equipConsum) {
        connect(ui->equipConsum, &QComboBox::currentTextChanged, this, &MainWindow::onUpdateConsumableChanged);
    }

    QTimer::singleShot(0, this, [this]() {
        if(ui->tableView_3) {
            QItemSelectionModel *selectionModel = ui->tableView_3->selectionModel();
            if (selectionModel) {
                disconnect(selectionModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::onUpdateTableSelectionChanged);
                connect(selectionModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::onUpdateTableSelectionChanged);
            } else {
                qDebug() << "Warning: Could not get selection model for tableView_3 (via QTimer). Connection failed.";
            }
        } else {
            qDebug() << "Warning: tableView_3 is null, cannot connect selection model.";
        }
    });

    if(!ui->export_2) { qDebug() << "Warning: export_2 button not found."; }

}


void MainWindow::loadEquipmentTable()
{
    if (!m_mainModel) {
        m_mainModel = new QSqlTableModel(this);
        m_mainModel->setTable("EQUIPMENT");
        m_mainModel->setHeaderData(0, Qt::Horizontal, "ID");
        m_mainModel->setHeaderData(1, Qt::Horizontal, "Name");
        m_mainModel->setHeaderData(2, Qt::Horizontal, "Type");
        m_mainModel->setHeaderData(3, Qt::Horizontal, "Status");
        m_mainModel->setHeaderData(4, Qt::Horizontal, "Maint. Date");
        m_mainModel->setHeaderData(5, Qt::Horizontal, "Quantity");
        m_mainModel->setHeaderData(6, Qt::Horizontal, "Purch. Date");
        m_mainModel->setHeaderData(7, Qt::Horizontal, "Price");
        m_mainModel->setHeaderData(8, Qt::Horizontal, "Dangerous");
        m_mainModel->setHeaderData(9, Qt::Horizontal, "Consumable");
        ui->equipmentTableView->setModel(m_mainModel);
        ui->equipmentTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->equipmentTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->equipmentTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->equipmentTableView->verticalHeader()->setVisible(false);
        ui->equipmentTableView->horizontalHeader()->setStretchLastSection(true);
    }
    if (!m_mainModel->select()) {
        qDebug() << "!!! Failed to select data for main table:" << m_mainModel->lastError().text();
    } else {
        qDebug() << "Main table model selected" << m_mainModel->rowCount() << "rows.";
    }
    ui->equipmentTableView->resizeColumnsToContents();
}


void MainWindow::loadUpdateEquipmentTable()
{
    if (!m_updateModel) {
        m_updateModel = new QSqlTableModel(this);
        m_updateModel->setTable("EQUIPMENT");
        m_updateModel->setHeaderData(0, Qt::Horizontal, "ID");
        m_updateModel->setHeaderData(1, Qt::Horizontal, "Name");
        m_updateModel->setHeaderData(2, Qt::Horizontal, "Type");
        m_updateModel->setHeaderData(3, Qt::Horizontal, "Status");
        m_updateModel->setHeaderData(4, Qt::Horizontal, "Maintenance");
        m_updateModel->setHeaderData(5, Qt::Horizontal, "Qty");
        m_updateModel->setHeaderData(6, Qt::Horizontal, "Purchased");
        m_updateModel->setHeaderData(7, Qt::Horizontal, "Price");
        m_updateModel->setHeaderData(8, Qt::Horizontal, "Dangerous");
        m_updateModel->setHeaderData(9, Qt::Horizontal, "Consumable");
        ui->tableView_3->setModel(m_updateModel);
        ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_3->verticalHeader()->setVisible(false);
        ui->tableView_3->horizontalHeader()->setStretchLastSection(true);

        QItemSelectionModel *selectionModel = ui->tableView_3->selectionModel();
        if (selectionModel) {
            disconnect(selectionModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::onUpdateTableSelectionChanged);
            connect(selectionModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::onUpdateTableSelectionChanged);
        } else {
            qDebug() << "Warning: Could not get selection model for tableView_3 (in loadUpdateEquipmentTable).";
        }

    }
    if (!m_updateModel->select()) {
        qDebug() << "!!! Failed to select data for update table (tableView_3):" << m_updateModel->lastError().text();
    } else {
        qDebug() << "Update table (tableView_3) model selected" << m_updateModel->rowCount() << "rows.";
    }
    ui->tableView_3->resizeColumnsToContents();
}

void MainWindow::loadDeleteEquipmentTable()
{
    if (!m_deleteModel) {
        m_deleteModel = new QSqlTableModel(this);
        m_deleteModel->setTable("EQUIPMENT");
        m_deleteModel->setHeaderData(0, Qt::Horizontal, "ID");
        m_deleteModel->setHeaderData(1, Qt::Horizontal, "Name");
        m_deleteModel->setHeaderData(2, Qt::Horizontal, "Type");
        m_deleteModel->setHeaderData(3, Qt::Horizontal, "Status");
        ui->tableView_4->setModel(m_deleteModel);
        ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_4->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_4->verticalHeader()->setVisible(false);
        ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
    }
    if (!m_deleteModel->select()) {
        qDebug() << "!!! Failed to select data for delete table (tableView_4):" << m_deleteModel->lastError().text();
    } else {
        qDebug() << "Delete table (tableView_4) model selected" << m_deleteModel->rowCount() << "rows.";
    }
    ui->tableView_4->resizeColumnsToContents();
}

void MainWindow::updateDashboardCounts()
{
    QSqlQuery query;
    int totalCount = 0, nonFunctionalCount = 0, maintenanceCount = 0, consumableCount = 0;
    if (query.exec("SELECT COUNT(*) FROM EQUIPMENT") && query.next()) { totalCount = query.value(0).toInt(); }
    else { qDebug() << "Error executing total count query:" << query.lastError().text(); }
    query.finish();
    query.prepare("SELECT COUNT(*) FROM EQUIPMENT WHERE UPPER(STATUS) = UPPER(:status)");
    query.bindValue(":status", "Not Working");
    if (query.exec() && query.next()) { nonFunctionalCount = query.value(0).toInt(); }
    else { qDebug() << "Error executing non-functional count query:" << query.lastError().text(); }
    query.finish();
    query.bindValue(":status", "Under Maintenance");
    if (query.exec() && query.next()) { maintenanceCount = query.value(0).toInt(); }
    else { qDebug() << "Error executing maintenance count query:" << query.lastError().text(); }
    query.finish();
    query.prepare("SELECT COUNT(*) FROM EQUIPMENT WHERE UPPER(CONSUMABLE) = UPPER(:consumable)");
    query.bindValue(":consumable", "Yes");
    if (query.exec() && query.next()) { consumableCount = query.value(0).toInt(); }
    else { qDebug() << "Error executing consumable count query:" << query.lastError().text(); }

    if(ui->label_6) ui->label_6->setText(QString("%1").arg(totalCount, 3, 10, QChar('0')));
    if(ui->label_7) ui->label_7->setText(QString("%1").arg(nonFunctionalCount, 3, 10, QChar('0')));
    if(ui->label_8) ui->label_8->setText(QString("%1").arg(maintenanceCount, 3, 10, QChar('0')));
    if(ui->label_16) ui->label_16->setText(QString("%1").arg(consumableCount, 3, 10, QChar('0')));
}

void MainWindow::onAddConsumableChanged(const QString &text)
{
    bool isConsumable = (text.compare("Yes", Qt::CaseInsensitive) == 0);
    if (ui->DNM) { ui->DNM->setVisible(!isConsumable); }
    else { qDebug() << "Warning: ui->DNM not found for visibility toggle."; }
    if (ui->equipDOM) { ui->equipDOM->setVisible(!isConsumable); }
    else { qDebug() << "Warning: ui->equipDOM not found for visibility toggle."; }
}

void MainWindow::onUpdateConsumableChanged(const QString &text)
{
    bool isConsumable = (text.compare("Yes", Qt::CaseInsensitive) == 0);
    if (ui->DNM_2) { ui->DNM_2->setVisible(!isConsumable); }
    else { qDebug() << "Warning: ui->DNM_2 not found for visibility toggle."; }
    if (ui->equipDOM_2) { ui->equipDOM_2->setVisible(!isConsumable); }
    else { qDebug() << "Warning: ui->equipDOM_2 not found for visibility toggle."; }
}


void MainWindow::onUpdateTableSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid()) {
        m_selectedUpdateId.clear(); return;
    }
    int selectedRow = current.row();
    QAbstractItemModel *model = m_updateModel;
    if (!model) { return; }
    const int idColumnIndex = 0;
    m_selectedUpdateId = model->data(model->index(selectedRow, idColumnIndex)).toString();

    QString name = model->data(model->index(selectedRow, 1)).toString();
    QString type = model->data(model->index(selectedRow, 2)).toString();
    QString status = model->data(model->index(selectedRow, 3)).toString();
    QDate maintDate = model->data(model->index(selectedRow, 4)).toDate();
    int quantity = model->data(model->index(selectedRow, 5)).toInt();
    QDate purchaseDate = model->data(model->index(selectedRow, 6)).toDate();
    double price = model->data(model->index(selectedRow, 7)).toDouble();
    QString dangerous = model->data(model->index(selectedRow, 8)).toString();
    QString consumable = model->data(model->index(selectedRow, 9)).toString();
    ui->equipName_3->setText(name); ui->equipType_6->setCurrentText(type); ui->equipState_2->setCurrentText(status);
    ui->equipDOM_2->setDate(maintDate); ui->equipQuantity_2->setText(QString::number(quantity));
    ui->equipPurchase_2->setDate(purchaseDate); ui->equipPrice_2->setText(QString::number(price));
    ui->equipDanger->setCurrentText(dangerous); ui->equipConsum->setCurrentText(consumable);

    onUpdateConsumableChanged(consumable);
}


void MainWindow::on_pushButton_13_clicked()
{
    if (m_selectedUpdateId.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select an item from the table to update."); return;
    }
    Equipment updatedEquip;
    updatedEquip.id = m_selectedUpdateId;
    updatedEquip.name = ui->equipName_3->text().trimmed();
    updatedEquip.type = ui->equipType_6->currentText();
    updatedEquip.status = ui->equipState_2->currentText();
    updatedEquip.purchaseDate = ui->equipPurchase_2->date();
    updatedEquip.dangerous = ui->equipDanger->currentText();
    updatedEquip.consumable = ui->equipConsum->currentText();

    bool quantityOk;
    updatedEquip.quantity = ui->equipQuantity_2->text().toInt(&quantityOk);
    if (!quantityOk) { QMessageBox::warning(this, "Input Error", "Invalid quantity."); return; }

    bool priceOk;
    updatedEquip.initialPrice = ui->equipPrice_2->text().toDouble(&priceOk);
    if (!priceOk) { QMessageBox::warning(this, "Input Error", "Invalid price."); return; }

    if (updatedEquip.name.isEmpty()) { QMessageBox::warning(this, "Input Error", "Name cannot be empty."); return; }

    if (updatedEquip.consumable.compare("Yes", Qt::CaseInsensitive) == 0) {
        updatedEquip.maintenanceDate = QVariant(QMetaType(QMetaType::QDate));
    } else {
        updatedEquip.maintenanceDate = QVariant::fromValue(ui->equipDOM_2->date());
    }

    bool success = DatabaseManager::instance().updateEquipment(updatedEquip);
    if (success) {
        QMessageBox::information(this, "Success", QString("Equipment ID %1 updated.").arg(updatedEquip.id));
        loadUpdateEquipmentTable();
        m_selectedUpdateId.clear(); ui->tableView_3->clearSelection();
        updateDashboardCounts();
    } else {
        QMessageBox::critical(this, "Error", QString("Failed to update equipment ID %1.").arg(updatedEquip.id));
    }
}

void MainWindow::on_deleteEquipButton_2_clicked()
{
    if (!ui || !ui->tableView_4) { return; }
    QItemSelectionModel *selectModel = ui->tableView_4->selectionModel();
    if (!selectModel) { return; }

    const QModelIndex currentIndex = selectModel->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select an item from the table to delete."); return;
    }

    int selectedRow = currentIndex.row();
    QAbstractItemModel *model = m_deleteModel;
    if (!model) { return; }

    const int idColumnIndex = 0; const int nameColumnIndex = 1;
    if (idColumnIndex >= model->columnCount() || nameColumnIndex >= model->columnCount()) { return; }
    QModelIndex idIndex = model->index(selectedRow, idColumnIndex);
    QModelIndex nameIndex = model->index(selectedRow, nameColumnIndex);
    if (!idIndex.isValid() || !nameIndex.isValid()) { return; }

    QString idToDelete = model->data(idIndex).toString();
    QString nameToDelete = model->data(nameIndex).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  QString("Are you sure you want to delete '%1' (ID: %2)?").arg(nameToDelete).arg(idToDelete),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool success = DatabaseManager::instance().deleteEquipment(idToDelete);
        if (success) {
            QMessageBox::information(this, "Success", QString("Equipment '%1' deleted successfully.").arg(nameToDelete));
            loadDeleteEquipmentTable();
            updateDashboardCounts();
        } else {
            QMessageBox::critical(this, "Error", QString("Failed to delete equipment '%1'.").arg(nameToDelete));
        }
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    Equipment newEquip;
    newEquip.name = ui->equipName->text().trimmed();
    newEquip.type = ui->equipType->currentText();
    newEquip.status = ui->equipState->currentText();
    newEquip.purchaseDate = ui->equipPurchaseDate->date();
    newEquip.dangerous = ui->equipType_4->currentText();
    newEquip.consumable = ui->equipType_3->currentText();

    bool quantityOk;
    newEquip.quantity = ui->equipQuantity->text().toInt(&quantityOk);
    if (!quantityOk) { QMessageBox::warning(this, "Input Error", "Invalid quantity."); return; }


    bool priceOk;
    newEquip.initialPrice = ui->equipPrice->text().toDouble(&priceOk);
    if (!priceOk) { QMessageBox::warning(this, "Input Error", "Invalid price."); return; }


    if (newEquip.name.isEmpty()) { QMessageBox::warning(this, "Input Error", "Name is required."); return; }

    if (newEquip.consumable.compare("Yes", Qt::CaseInsensitive) == 0) {
        newEquip.maintenanceDate = QVariant(QMetaType(QMetaType::QDate));
    } else {
        if(ui->equipDOM) {
            newEquip.maintenanceDate = QVariant::fromValue(ui->equipDOM->date());
        } else {
            qDebug() << "Error: ui->equipDOM not found when trying to get non-consumable date.";
            QMessageBox::critical(this, "Internal Error", "Maintenance Date field not found.");
            return;
        }
    }

    bool success = DatabaseManager::instance().addEquipment(newEquip);
    if (success) {
        QMessageBox::information(this, "Success", "Equipment added successfully!");
        updateDashboardCounts();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add equipment.");
    }
}

void MainWindow::applyFilter(QSqlTableModel *model, const QString &searchText)
{
    if (!model) { return; }
    QString filter;
    if (!searchText.isEmpty()) {
        QString escapedSearchText = searchText;
        escapedSearchText.replace("'", "''");
        QStringList filterParts;
        filterParts << QString("UPPER(ID_EQUIPMENT) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(NAME) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(TYPE) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(STATUS) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(TO_CHAR(MAINTENANCE_DATE)) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(TO_CHAR(QUANTITY)) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(TO_CHAR(PURCHASE_DATE)) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(TO_CHAR(INITIAL_PRICE)) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(DANGEROUS) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filterParts << QString("UPPER(CONSUMABLE) LIKE UPPER('%%1%')").arg(escapedSearchText);
        filter = filterParts.join(" OR ");
    }

    model->setFilter(filter);
    if (!model->select()) {
        qDebug() << "!!! Failed to select data after applying filter:" << model->lastError().text();
    } else {
        if (model == m_mainModel) {
            updateDashboardCounts();
        }
    }
}

void MainWindow::onSearchTextChanged(const QString &searchText)
{
    applyFilter(m_mainModel, searchText);
}

void MainWindow::onUpdateSearchTextChanged(const QString &searchText)
{
    applyFilter(m_updateModel, searchText);
}

void MainWindow::on_searchTextBox_2_textChanged(const QString &searchText)
{
    applyFilter(m_deleteModel, searchText);
}

QString MainWindow::escapeCsv(const QString &input)
{
    QString result = input;
    result.replace('"', "\"\"");
    if (result.contains(',') || result.contains('\n') || result.contains('"')) {
        result = "\"" + result + "\"";
    }
    return result;
}

void MainWindow::on_export_2_clicked()
{
    qDebug() << "Export button clicked.";
    if (!m_mainModel) {
        QMessageBox::warning(this, "Export Error", "No data model loaded to export.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Equipment Data", "", "CSV Files (*.csv);;All Files (*)");

    if (fileName.isEmpty()) {
        qDebug() << "Export cancelled by user.";
        return;
    }

    if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        fileName += ".csv";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", QString("Could not open file for writing:\n%1").arg(file.errorString()));
        qDebug() << "Error opening file" << fileName << "for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << escapeCsv("Category") << "," << escapeCsv("Count") << "\n";

    QTextDocument textDoc;
    QString plainText;

    if(ui->label && ui->label_6) {
        textDoc.setHtml(ui->label->text());
        plainText = textDoc.toPlainText().trimmed();
        out << escapeCsv(plainText) << "," << escapeCsv(ui->label_6->text()) << "\n";
    }
    if(ui->label_4 && ui->label_7) {
        textDoc.setHtml(ui->label_4->text());
        plainText = textDoc.toPlainText().trimmed();
        out << escapeCsv(plainText) << "," << escapeCsv(ui->label_7->text()) << "\n";
    }
    if(ui->label_5 && ui->label_8) {
        textDoc.setHtml(ui->label_5->text());
        plainText = textDoc.toPlainText().trimmed();
        out << escapeCsv(plainText) << "," << escapeCsv(ui->label_8->text()) << "\n";
    }
    if(ui->label_11 && ui->label_16) {
        textDoc.setHtml(ui->label_11->text());
        plainText = textDoc.toPlainText().trimmed();
        out << escapeCsv(plainText) << "," << escapeCsv(ui->label_16->text()) << "\n";
    }

    out << "\n";
    QStringList headers;
    for (int col = 0; col < m_mainModel->columnCount(); ++col) {
        headers << escapeCsv(m_mainModel->headerData(col, Qt::Horizontal).toString());
    }
    out << headers.join(',') << "\n";

    for (int row = 0; row < m_mainModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < m_mainModel->columnCount(); ++col) {
            QVariant data = m_mainModel->data(m_mainModel->index(row, col));
            QString dataString;
            if (data.typeId() == QMetaType::QDate) {
                dataString = data.toDate().toString(Qt::ISODate);
            } else if (data.typeId() == QMetaType::Double) {
                dataString = QString::number(data.toDouble(), 'f', 2);
            } else {
                dataString = data.toString();
            }
            rowData << escapeCsv(dataString);
        }
        out << rowData.join(',') << "\n";
    }

    file.close();

    if (file.error() == QFile::NoError) {
        QMessageBox::information(this, "Export Successful", QString("Data exported successfully to:\n%1").arg(fileName));
        qDebug() << "Data exported successfully to" << fileName;
    } else {
        QMessageBox::critical(this, "Export Error", QString("An error occurred while writing the file:\n%1").arg(file.errorString()));
        qDebug() << "Error writing file" << fileName << ":" << file.errorString();
    }
}

void MainWindow::showStatsChart() {
    int total, nonFunc, maint, consum;
    // Fetch counts from the database
    if (!DatabaseManager::instance().getEquipmentCounts(total, nonFunc, maint, consum)) {
        qDebug() << "Failed to fetch equipment counts for chart.";
        // QMessageBox::warning(this, "Chart Error", "Could not load chart data.");
        return;
    }

    // Get the container widget (replace 'widget' if needed) and its layout
    QWidget *chartContainer = ui->widget;
    if (!chartContainer) {
        qDebug() << "Chart container widget (ui->widget) not found.";
        return;
    }
    QLayout *layout = chartContainer->layout();

    // Clear previous chart/widgets from the layout
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            // Properly delete widget and layout item
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    } else {
        // Create layout if it doesn't exist
        layout = new QVBoxLayout(chartContainer);
        chartContainer->setLayout(layout);
    }

    // Handle case with no data or invalid counts
    if (total <= 0) {
        qDebug() << "No equipment data or zero total count.";
        QLabel *noDataLabel = new QLabel("No equipment data to display.", chartContainer);
        noDataLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(noDataLabel);
        return;
    }

    // Create the pie series
    QPieSeries *series = new QPieSeries();

    // Calculate 'Other' count
    int otherCount = total - nonFunc - maint - consum;
    if (otherCount < 0) otherCount = 0; // Ensure non-negative

    // --- Store Category Names ---
    // We store the names separately to reliably set legend labels later
    QStringList categoryNames;
    QList<qreal> categoryValues;

    if (nonFunc > 0) { categoryNames << "Non-functional"; categoryValues << nonFunc; }
    if (maint > 0) { categoryNames << "Maintenance"; categoryValues << maint; }
    if (consum > 0) { categoryNames << "Consumable"; categoryValues << consum; }
    if (otherCount > 0) { categoryNames << "Other"; categoryValues << otherCount; }

    // Append slices using the stored values
    for(int i = 0; i < categoryNames.size(); ++i) {
        series->append(categoryNames[i], categoryValues[i]);
    }
    // --- End Storing Category Names ---


    // Configure slice labels to show percentages
    series->setLabelsVisible(true);
    for(QPieSlice *slice : series->slices()) {
        // Set the label ON THE SLICE to be the percentage
        slice->setLabel(QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1));
        // Optional: Customize label appearance (e.g., font, color)
        // slice->setLabelBrush(Qt::white);
        // slice->setLabelFont(QFont("Arial", 8));
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series); // Add series BEFORE configuring legend markers
    chart->setTitle("Equipment Status Distribution");

    // Configure the legend explicitly
    QLegend *legend = chart->legend();
    legend->setVisible(true);
    legend->setAlignment(Qt::AlignRight); // Position legend on the right

    // --- Force Legend Labels to be Category Names ---
    // Iterate through the legend markers and set their labels explicitly
    // using the stored category names.
    const auto markers = legend->markers(series); // Get markers for the specific series
    // Ensure we have the same number of markers as categories added
    if (markers.size() == categoryNames.size()) {
        for (int i = 0; i < markers.size(); ++i) {
            // Set the marker's label to the corresponding stored category name
            markers[i]->setLabel(categoryNames[i]);
        }
    } else {
        qDebug() << "Warning: Mismatch between legend markers and category names count.";
        // Fallback or default legend behavior will apply
    }
    // --- End Legend Label Fix ---


    // Optional: Improve legend appearance
    // legend->setFont(QFont("Arial", 10));
    // legend->setMarkerShape(QLegend::MarkerShapeCircle); // Example: Circle markers

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add chart view to the layout
    layout->addWidget(chartView);
}
