#ifndef EXPERIMENTS_H
#define EXPERIMENTS_H

#include <QString>
#include <QDate>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Experiments
{
private:
    int experiment_id;
    QString name;
    QString description;
    QString protocol;
    QString status;
    QDate start_date;
    QDate end_date;
    QString results_obtained;
    QString responsible_name;

public:
    Experiments(int id = 0, QString name = "", QString desc = "", QString prot = "",
                QString stat = "", QDate start = QDate(), QDate end = QDate(), QString resultsObtained = "",QString responsibleName = "" );

    // Database methods
    bool add();
    QSqlQueryModel* read();
    bool remove(int id);  // Changed from 'delete' which is a reserved keyword
    bool update(int id, const QString &name, const QString &description, const QString &protocol,const QString &status, const QDate &startDate, const QDate &endDate, const QString &resultsObtained, const QString &responsibleName);

    // Getters
    int getExperimentId() const { return experiment_id; }
    QString getName() const { return name; }
    QString getDescription() const { return description; }
    QString getProtocol() const { return protocol; }
    QString getStatus() const { return status; }
    QDate getStartDate() const { return start_date; }
    QDate getEndDate() const { return end_date; }
    QString getResulsObtained() const { return results_obtained; }
    QString getResponsibleName() const { return responsible_name; }
};

#endif // EXPERIMENTS_H
