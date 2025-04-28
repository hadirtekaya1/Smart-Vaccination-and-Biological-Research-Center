#include "vaccine.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

Vaccine::Vaccine() : stockQuantity(0) {}

Vaccine::Vaccine(QString name, QString type, QDate manufacturingDate,
                 QDate expirationDate, QString batchNumber, QString supplier, int stockQuantity) :
    name(name), type(type), manufacturingDate(manufacturingDate),
    expirationDate(expirationDate), batchNumber(batchNumber), supplier(supplier),
    stockQuantity(stockQuantity) {}

QString Vaccine::getId() { return id; }
QString Vaccine::getName() { return name; }
QString Vaccine::getType() { return type; }
QDate Vaccine::getManufacturingDate() { return manufacturingDate; }
QDate Vaccine::getExpirationDate() { return expirationDate; }
QString Vaccine::getBatchNumber() { return batchNumber; }
QString Vaccine::getSupplier() { return supplier; }
int Vaccine::getStockQuantity() { return stockQuantity; }

bool Vaccine::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO vaccine (VACCINE_NAME, TYPE, MANUFACTURING_DATE, "
                  "EXPIRATION_DATE, BATCH_NUMBER, SUPPLIER, STOCK_QUANTITY) "
                  "VALUES (:name, :type, :manufacturing_date, "
                  ":expiration_date, :batch_number, :supplier, :stock_quantity)");

    //query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    query.bindValue(":manufacturing_date", manufacturingDate);
    query.bindValue(":expiration_date", expirationDate);
    query.bindValue(":batch_number", batchNumber);
    query.bindValue(":supplier", supplier);
    query.bindValue(":stock_quantity", stockQuantity);

    return query.exec();
}

QSqlQueryModel* Vaccine::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM vaccine");
    return model;
}

bool Vaccine::modifier(QString vacid) {
    QSqlQuery query;
    query.prepare("UPDATE vaccine SET VACCINE_NAME = :name, TYPE = :type, "
                  "MANUFACTURING_DATE = :manufacturing_date, "
                  "EXPIRATION_DATE = :expiration_date, "
                  "BATCH_NUMBER = :batch_number, SUPPLIER = :supplier, "
                  "STOCK_QUANTITY = :stock_quantity WHERE ID_VACCINE = :vacid");

    query.bindValue(":vacid", vacid);
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    query.bindValue(":manufacturing_date", manufacturingDate);
    query.bindValue(":expiration_date", expirationDate);
    query.bindValue(":batch_number", batchNumber);
    query.bindValue(":supplier", supplier);
    query.bindValue(":stock_quantity", stockQuantity);

    return query.exec();
}

bool Vaccine::supprimer(QString vacid) {
    QSqlQuery query;
    query.prepare("DELETE FROM vaccine WHERE ID_VACCINE = :vacid");
    query.bindValue(":vacid", vacid);
    return query.exec();
}
