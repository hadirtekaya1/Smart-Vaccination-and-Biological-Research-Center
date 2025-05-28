#include "pdfexporter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include <QPageSize>
#include <QPageLayout>

PDFExporter::PDFExporter(QObject *parent) : QObject(parent)
{
}

bool PDFExporter::exportToPDF(QTableWidget *table, const QString &title, const QString &fileName)
{
    if (!table || table->rowCount() == 0)
        return false;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(generateHTML(table, title));
    doc.setPageSize(printer.pageLayout().paintRectPixels(printer.resolution()).size());
    doc.print(&printer);

    return true;
}

QString PDFExporter::generateHTML(QTableWidget *table, const QString &title)
{
    QString html = QString(
                       "<html>"
                       "<head>"
                       "<style>"
                       "body { font-family: Arial; margin: 20px; }"
                       "h1 { color: #144976; text-align: center; margin-bottom: 30px; }"
                       "table { border-collapse: collapse; width: 100%; margin-top: 20px; }"
                       "th { background-color: #144976; color: white; padding: 12px; text-align: left; }"
                       "td { padding: 10px; border: 1px solid #ddd; }"
                       "tr:nth-child(even) { background-color: #f8f8f8; }"
                       "tr:hover { background-color: #f0f0f0; }"
                       "</style>"
                       "</head>"
                       "<body>"
                       "<h1>%1</h1>"
                       "<table>"
                       ).arg(title);

    // Add headers
    html += "<tr>";
    for (int col = 0; col < table->columnCount(); ++col) {
        if (table->horizontalHeaderItem(col)) {
            html += "<th>" + table->horizontalHeaderItem(col)->text() + "</th>";
        }
    }
    html += "</tr>";

    // Add data rows
    for (int row = 0; row < table->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->item(row, col);
            html += "<td>" + (item ? item->text() : "") + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>"
            "<div style='margin-top: 30px; text-align: right; font-style: italic;'>"
            "Generated on " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") +
            "</div>"
            "</body></html>";
    return html;
}
