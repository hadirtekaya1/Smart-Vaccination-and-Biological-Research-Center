#include "resultshistory.h"
#include "ui_resultshistory.h"
#include "experiments.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>       // ← celui qu’il te manquait
#include <QSqlError>
#include <QRect>


ResultsHistory::ResultsHistory(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResultsHistory)
{
    ui->setupUi(this);
    ui->tableWidgetResults->setColumnCount(4);
    ui->tableWidgetResults->setHorizontalHeaderLabels(
        {"Name", "Responsible", "Date", "Result"});

    // Load responsible names combo box
    QSqlQuery query;
    query.exec("SELECT DISTINCT RESPONSIBLE_NAME FROM EXPERIMENTS");
    ui->comboBoxResponsible->addItem("All");
    while(query.next()) {
        ui->comboBoxResponsible->addItem(query.value(0).toString());
    }

    // Set default date to today
    ui->dateEditFilter->setDate(QDate::currentDate());

    // Connect signals
    connect(ui->backButton, &QPushButton::clicked,
            this, &ResultsHistory::backRequested);
    connect(ui->exportPDFButton, &QPushButton::clicked,
            this, &ResultsHistory::on_exportPDFButton_clicked);
    connect(ui->viewDetailsButton, &QPushButton::clicked,
            this, &ResultsHistory::on_viewDetailsButton_clicked);
    connect(ui->comboBoxResponsible, &QComboBox::currentTextChanged,
            this, &ResultsHistory::applyFilters);
    connect(ui->dateEditFilter, &QDateEdit::dateChanged,
            this, &ResultsHistory::applyFilters);


    // Load initial data
    loadData();
}

ResultsHistory::~ResultsHistory()
{
    delete ui;
}
void ResultsHistory::loadData() {
    // Clear existing data
    experimentList.clear();
    ui->tableWidgetResults->setRowCount(0);

    // Verify database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
        return;
    }

    // Load data
    Experiments expModel;
    QSqlQueryModel* model = expModel.read();

    if (model->rowCount() == 0) {
        qDebug() << "Aucune expérience trouvée dans la base";
        QMessageBox::information(this, "Information", "Aucune expérience trouvée");
        return;
    }

    // Remplir la liste d’expériences
    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);

        Experiments exp(
            record.value("EXPERIMENT_ID").toInt(),
            record.value("NAME").toString(),
            record.value("DESCRIPTION").toString(),
            record.value("PROTOCOL").toString(),
            record.value("STATUS").toString(),
            record.value("START_DATE").toDate(),
            record.value("END_DATE").toDate(),
            record.value("RESULTS_OBTAINED").toString(),
            record.value("RESPONSIBLE_NAME").toString()
            );

        experimentList.append(exp);
    }

    // Appel des filtres pour affichage dynamique
    applyFilters();

    qDebug() << "Chargé" << experimentList.size() << "expériences depuis la base";
}

bool ResultsHistory::isFiltered(const Experiments& exp) {
    QDate endDate = exp.getEndDate();
    QDate selectedDate = ui->dateEditFilter->date();
    QString selectedResponsible = ui->comboBoxResponsible->currentText();

    // Ignorer les expériences sans date de fin valide
    if (!endDate.isValid())
        return false;

    return (endDate <= selectedDate &&
            (selectedResponsible == "All" || exp.getResponsibleName() == selectedResponsible));
}

void ResultsHistory::applyFilters() {
    ui->tableWidgetResults->setRowCount(0); // Clear table
    filteredList.clear(); // Clear filtered list

    for (const Experiments& exp : experimentList) {
        if (!isFiltered(exp))
            continue;

        int row = ui->tableWidgetResults->rowCount();
        ui->tableWidgetResults->insertRow(row);
        ui->tableWidgetResults->setItem(row, 0, new QTableWidgetItem(exp.getName()));
        ui->tableWidgetResults->setItem(row, 1, new QTableWidgetItem(exp.getResponsibleName()));
        ui->tableWidgetResults->setItem(row, 2, new QTableWidgetItem(exp.getEndDate().toString("yyyy-MM-dd")));
        ui->tableWidgetResults->setItem(row, 3, new QTableWidgetItem(exp.getResulsObtained()));

        filteredList.append(exp); // Garde l’ordre exact affiché
    }

    qDebug() << "Filtered results displayed:" << filteredList.size() << "entries.";
}



void ResultsHistory::on_backButton_clicked()
{
    this->close();
    emit backRequested();
}


void ResultsHistory::on_exportPDFButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));
    if (fileName.isEmpty())
        return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);
    QPainter painter(&writer);

    int pageWidth = writer.width();
    int pageHeight = writer.height();
    int margin = 50;
    int y = margin;
    int rowHeight = 60;

    QFont titleFont("Arial", 18, QFont::Bold);
    QFont headerFont("Arial", 12, QFont::Bold);
    QFont contentFont("Arial", 11);
    QFont footerFont("Arial", 9, QFont::Bold);

    // Draw logo (larger)
    QPixmap logo(":/images/logo.jpg");
    if (!logo.isNull()) {
        QPixmap scaledLogo = logo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(margin, y, scaledLogo);
    }

    // Title (next to logo)
    painter.setFont(titleFont);
    QRect titleRect(margin + 120, y + 30, pageWidth - 2 * margin - 120, 100);  // Shift right to avoid logo
    painter.drawText(titleRect, Qt::AlignLeft | Qt::AlignVCenter, "Experiment Results History");

    y += 120;

    // Table headers
    painter.setFont(headerFont);
    painter.setBrush(QColor(220, 220, 220));
    painter.setPen(Qt::black);
    painter.drawRect(margin, y, pageWidth - 2 * margin, rowHeight);

    int col1Width = (pageWidth - 2 * margin) * 0.3;
    int col2Width = (pageWidth - 2 * margin) * 0.4;
    int col3Width = (pageWidth - 2 * margin) * 0.3;

    QRect nameHeader(margin + 10, y, col1Width, rowHeight);
    QRect responsibleHeader(margin + col1Width + 10, y, col2Width, rowHeight);
    QRect dateHeader(margin + col1Width + col2Width + 10, y, col3Width, rowHeight);

    painter.drawText(nameHeader, Qt::AlignLeft | Qt::AlignVCenter, "Name");
    painter.drawText(responsibleHeader, Qt::AlignLeft | Qt::AlignVCenter, "Responsible");
    painter.drawText(dateHeader, Qt::AlignLeft | Qt::AlignVCenter, "End Date");

    y += rowHeight;
    painter.setFont(contentFont);

    for (const Experiments& exp : filteredList) {
        if (y > pageHeight - margin * 2) {
            drawFooter(&painter, writer, footerFont);
            writer.newPage();
            y = margin + 120;
        }

        painter.setPen(QPen(Qt::gray, 0.5));
        painter.drawLine(margin, y, pageWidth - margin, y);
        painter.setPen(Qt::black);

        QRect nameRect(margin + 10, y, col1Width, rowHeight);
        QRect responsibleRect(margin + col1Width + 10, y, col2Width, rowHeight);
        QRect dateRect(margin + col1Width + col2Width + 10, y, col3Width, rowHeight);

        painter.drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, exp.getName());
        painter.drawText(responsibleRect, Qt::AlignLeft | Qt::AlignVCenter, exp.getResponsibleName());
        painter.drawText(dateRect, Qt::AlignLeft | Qt::AlignVCenter, exp.getEndDate().toString("yyyy-MM-dd"));

        y += rowHeight;
    }

    drawFooter(&painter, writer, footerFont);
    painter.end();
    QMessageBox::information(this, "Export PDF", "PDF exported successfully!");
}


void ResultsHistory::drawFooter(QPainter* painter, QPdfWriter& writer, const QFont& font)
{
    painter->setFont(font);
    painter->setPen(Qt::darkGray);

    int margin = 50;
    int y = writer.height() - margin;

    // Footer text on top of the logo
    QString footerText = "Lab Management System - Exported on: " + QDate::currentDate().toString("yyyy-MM-dd");
    QRect footerRect(margin, y - 40, writer.width() - 2 * margin, 40);  // Adjusted for text positioning
    painter->setBrush(Qt::transparent); // Make sure text is on top and clear
    painter->drawText(footerRect, Qt::AlignCenter, footerText);
}


void ResultsHistory::on_viewDetailsButton_clicked()
{
    int selectedRow = ui->tableWidgetResults->currentRow();

    if (selectedRow < 0 || selectedRow >= filteredList.size()) {
        QMessageBox::warning(this, "Selection Error", "Please select a valid experiment.");
        return;
    }

    const Experiments& exp = filteredList[selectedRow];  // ← Prend dans filteredList, pas experimentList

    QString startDate = exp.getStartDate().isValid() ? exp.getStartDate().toString("yyyy-MM-dd") : "Not set";
    QString endDate = exp.getEndDate().isValid() ? exp.getEndDate().toString("yyyy-MM-dd") : "Not set";

    QString details = QString(
                          "<html><body style='font-family:Arial;'>"
                          "<h2 style='color:#2c3e50;'>Experiment Details</h2>"
                          "<table cellspacing='5' cellpadding='3'>"
                          "<tr><td style='font-weight:bold;'>ID:</td><td>%1</td></tr>"
                          "<tr><td style='font-weight:bold;'>Name:</td><td>%2</td></tr>"
                          "<tr><td style='font-weight:bold;'>Description:</td><td>%3</td></tr>"
                          "<tr><td style='font-weight:bold;'>Protocol:</td><td>%4</td></tr>"
                          "<tr><td style='font-weight:bold;'>Status:</td><td>%5</td></tr>"
                          "<tr><td style='font-weight:bold;'>Period:</td><td>%6 to %7</td></tr>"
                          "<tr><td style='font-weight:bold;'>Responsible:</td><td>%8</td></tr>"
                          "<tr><td style='font-weight:bold;'>Results:</td><td>%9</td></tr>"
                          "</table></body></html>")
                          .arg(exp.getExperimentId())
                          .arg(exp.getName())
                          .arg(exp.getDescription())
                          .arg(exp.getProtocol())
                          .arg(exp.getStatus())
                          .arg(startDate)
                          .arg(endDate)
                          .arg(exp.getResponsibleName())
                          .arg(exp.getResulsObtained());

    QMessageBox msgBox;
    msgBox.setWindowTitle("Experiment Details - " + exp.getName());
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(details);
    msgBox.exec();
}

