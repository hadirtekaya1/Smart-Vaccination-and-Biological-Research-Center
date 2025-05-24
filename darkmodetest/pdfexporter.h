#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QObject>
#include <QTableWidget>
#include <QPrinter>
#include <QPageSize>
#include <QPageLayout>
#include <QTextDocument>

class PDFExporter : public QObject
{
    Q_OBJECT
public:
    explicit PDFExporter(QObject *parent = nullptr);

    static bool exportToPDF(QTableWidget *table, const QString &title, const QString &fileName);

private:
    static QString generateHTML(QTableWidget *table, const QString &title);
};

#endif // PDFEXPORTER_H
