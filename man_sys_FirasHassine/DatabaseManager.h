#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>
#include <QVariant>

struct Equipment {
    QString id;
    QString name;
    QString type;
    QString status;
    QVariant maintenanceDate;
    int quantity = 0;
    QDate purchaseDate;
    double initialPrice = 0.0;
    QString dangerous;
    QString consumable;
    Equipment() = default;
};


class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool connectToDatabase();
    QSqlDatabase database() const;

    bool addEquipment(const Equipment &equipment);
    bool updateEquipment(const Equipment &equipment);
    bool deleteEquipment(const QString &id);
    bool getEquipmentCounts(int &total, int &nonFunc, int &maint, int &consum);

private:
    DatabaseManager();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
