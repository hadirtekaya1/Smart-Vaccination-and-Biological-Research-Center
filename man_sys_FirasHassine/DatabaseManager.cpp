#include "DatabaseManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QMetaType>

DatabaseManager::DatabaseManager() {}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

QSqlDatabase DatabaseManager::database() const {
    return db;
}

bool DatabaseManager::connectToDatabase() {
    QString connectionName = QSqlDatabase::defaultConnection;
    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
        if (db.isOpen()) { return true; }
        QSqlDatabase::removeDatabase(connectionName);
    }
    db = QSqlDatabase::addDatabase("QODBC", connectionName);
    db.setDatabaseName("Source_ProjetA2");
    db.setUserName("vaccination");
    db.setPassword("vaccination");
    if (!db.open()) {
        qDebug() << "Connection error:" << db.lastError().text();
        return false;
    }
    qDebug() << "Database connected successfully to" << db.databaseName();
    return true;
}

bool DatabaseManager::addEquipment(const Equipment &equipment) {
    if (!db.isOpen()) { return false; }
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO EQUIPMENT
        (NAME, TYPE, STATUS, MAINTENANCE_DATE, QUANTITY, PURCHASE_DATE, INITIAL_PRICE, DANGEROUS, CONSUMABLE)
        VALUES
        (:name, :type, :status, :date, :quantity, :purchaseDate, :initialPrice, :dangerous, :consumable)
    )");

    query.bindValue(":name", equipment.name);
    query.bindValue(":type", equipment.type);
    query.bindValue(":status", equipment.status);
    if (equipment.maintenanceDate.isNull() || !equipment.maintenanceDate.isValid() || !equipment.maintenanceDate.canConvert<QDate>()) {
        query.bindValue(":date", QVariant(QMetaType(QMetaType::QDate)));
    } else {
        query.bindValue(":date", equipment.maintenanceDate.toDate());
    }
    query.bindValue(":quantity", equipment.quantity);
    query.bindValue(":purchaseDate", equipment.purchaseDate);
    query.bindValue(":initialPrice", equipment.initialPrice);
    query.bindValue(":dangerous", equipment.dangerous);
    query.bindValue(":consumable", equipment.consumable);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text(); return false;
    }
    return true;
}

bool DatabaseManager::updateEquipment(const Equipment &equipment) {
    if (!db.isOpen()) { return false; }
    if (equipment.id.isEmpty()) { return false; }
    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE EQUIPMENT
        SET NAME = :name, TYPE = :type, STATUS = :status, MAINTENANCE_DATE = :date,
            QUANTITY = :quantity, PURCHASE_DATE = :purchaseDate, INITIAL_PRICE = :initialPrice,
            DANGEROUS = :dangerous, CONSUMABLE = :consumable
        WHERE ID_EQUIPMENT = :id
    )");

    query.bindValue(":name", equipment.name);
    query.bindValue(":type", equipment.type);
    query.bindValue(":status", equipment.status);
    if (equipment.maintenanceDate.isNull() || !equipment.maintenanceDate.isValid() || !equipment.maintenanceDate.canConvert<QDate>()) {
        query.bindValue(":date", QVariant(QMetaType(QMetaType::QDate)));
    } else {
        query.bindValue(":date", equipment.maintenanceDate.toDate());
    }
    query.bindValue(":quantity", equipment.quantity);
    query.bindValue(":purchaseDate", equipment.purchaseDate);
    query.bindValue(":initialPrice", equipment.initialPrice);
    query.bindValue(":dangerous", equipment.dangerous);
    query.bindValue(":consumable", equipment.consumable);
    query.bindValue(":id", equipment.id);

    if (!query.exec()) {
        qDebug() << "Update failed for ID" << equipment.id << ":" << query.lastError().text(); return false;
    }
    return true;
}

bool DatabaseManager::deleteEquipment(const QString &id) {
    if (!db.isOpen()) { return false; }
    if (id.isEmpty()) { return false; }
    QSqlQuery query(db);
    query.prepare("DELETE FROM EQUIPMENT WHERE ID_EQUIPMENT = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Delete failed for ID" << id << ":" << query.lastError().text(); return false;
    }
    return true;
}

bool DatabaseManager::getEquipmentCounts(int &total, int &nonFunc, int &maint, int &consum)
{
    if (!db.isOpen()) {
        total = nonFunc = maint = consum = -1; return false;
    }
    QSqlQuery query(db);
    bool ok = true;
    total = nonFunc = maint = consum = 0;

    if (query.exec("SELECT COUNT(*) FROM EQUIPMENT") && query.next()) { total = query.value(0).toInt(); }
    else { qDebug() << "Error executing total count query:" << query.lastError().text(); ok = false; }
    query.finish();

    query.prepare("SELECT COUNT(*) FROM EQUIPMENT WHERE UPPER(STATUS) = UPPER(:status)");
    query.bindValue(":status", "Not Working");
    if (query.exec() && query.next()) { nonFunc = query.value(0).toInt(); }
    else { qDebug() << "Error executing non-functional count query:" << query.lastError().text(); ok = false; }
    query.finish();

    query.bindValue(":status", "Under Maintenance");
    if (query.exec() && query.next()) { maint = query.value(0).toInt(); }
    else { qDebug() << "Error executing maintenance count query:" << query.lastError().text(); ok = false; }
    query.finish();

    query.prepare("SELECT COUNT(*) FROM EQUIPMENT WHERE UPPER(CONSUMABLE) = UPPER(:consumable)");
    query.bindValue(":consumable", "Yes");
    if (query.exec() && query.next()) { consum = query.value(0).toInt(); }
    else { qDebug() << "Error executing consumable count query:" << query.lastError().text(); ok = false; }

    return ok;
}
