#include "Experiments.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QObject>

Experiments::Experiments(int id, QString n, QString desc, QString prot,
                         QString stat, QDate start, QDate end ,QString res ,QString resn) :
    experiment_id(id), name(n), description(desc), protocol(prot),
    status(stat), start_date(start), end_date(end), results_obtained(res), responsible_name(resn) {}

bool Experiments::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EXPERIMENTS (EXPERIMENT_ID, NAME, DESCRIPTION, "
                  "PROTOCOL, STATUS, START_DATE, END_DATE, RESULTS_OBTAINED, RESPONSIBLE_NAME) "
                  "VALUES (:id, :name, :desc, :prot, :stat, :start, :end, :res, :resn)");

    query.bindValue(":id", experiment_id);
    query.bindValue(":name", name);
    query.bindValue(":desc", description);
    query.bindValue(":prot", protocol);
    query.bindValue(":stat", status);
    query.bindValue(":start", start_date);
    query.bindValue(":end", end_date);
    query.bindValue(":res", results_obtained);
    query.bindValue(":resn", responsible_name);

    if(!query.exec()) {
        qDebug() << "Error adding experiment:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Experiments::read()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT EXPERIMENT_ID, NAME, DESCRIPTION, PROTOCOL, STATUS, "
                    "START_DATE, END_DATE, RESULTS_OBTAINED, RESPONSIBLE_NAME "
                    "FROM EXPERIMENTS ORDER BY EXPERIMENT_ID");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la récupération des données:" << model->lastError().text();
    }


    // Set headers in correct order
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Protocol"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Start Date"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("End Date"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Results Obtained"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Responsible Name"));

    return model;
}

bool Experiments::update(int id, const QString &name, const QString &description, const QString &protocol,
                         const QString &status, const QDate &startDate, const QDate &endDate,
                         const QString &resultsObtained, const QString &responsibleName)
{
    QSqlQuery query;
    query.prepare("UPDATE EXPERIMENTS SET "
                  "NAME = :name, "
                  "DESCRIPTION = :description, "
                  "PROTOCOL = :protocol, "
                  "STATUS = :status, "
                  "START_DATE = :startDate, "
                  "END_DATE = :endDate, "
                  "RESULTS_OBTAINED = :resultsObtained, "
                  "RESPONSIBLE_NAME = :responsibleName "
                  "WHERE EXPERIMENT_ID = :id");

    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":protocol", protocol);
    query.bindValue(":status", status);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);
    query.bindValue(":resultsObtained", resultsObtained);
    query.bindValue(":responsibleName", responsibleName);

    if(!query.exec()) {
        qDebug() << "Update error:" << query.lastError();
        return false;
    }
    return true;
}
bool Experiments::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EXPERIMENTS WHERE EXPERIMENT_ID = :id");
    query.bindValue(":id", id);  // ← int directement, c’est mieux

    if (!query.exec()) {
        qDebug() << "Delete error:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}
