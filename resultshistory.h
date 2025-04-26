#ifndef RESULTSHISTORY_H
#define RESULTSHISTORY_H

#include <QWidget>
#include "experiments.h"

#include <QPainter>
#include <QPdfWriter>
#include <QFont>
#include <QDate>
#include <QString>

namespace Ui {
class ResultsHistory;
}

class ResultsHistory : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsHistory(QWidget *parent = nullptr);
    ~ResultsHistory();

    void loadData();
    void applyFilters();

signals:
    void backRequested();

private slots:
    void on_backButton_clicked();


    void on_exportPDFButton_clicked();

    void on_viewDetailsButton_clicked();

private:
    Ui::ResultsHistory *ui;
    QList<Experiments> experimentList;
    QList<Experiments> filteredList; // Liste filtrée affichée dans le tableau

    bool isFiltered(const Experiments& exp);
    void drawFooter(QPainter* painter, QPdfWriter& writer, const QFont& font);
};

#endif // RESULTSHISTORY_H
