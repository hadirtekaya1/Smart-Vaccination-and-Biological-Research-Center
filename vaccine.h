#ifndef VACCINE_H
#define VACCINE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Vaccine {
private:
    QString id;
    QString name;
    QString type;
    QDate manufacturingDate;
    QDate expirationDate;
    QString batchNumber;
    QString supplier;
    int stockQuantity;

public:
    Vaccine();
    Vaccine(QString, QString, QDate, QDate, QString, QString, int);

    QString getId();
    QString getName();
    QString getType();
    QDate getManufacturingDate();
    QDate getExpirationDate();
    QString getBatchNumber();
    QString getSupplier();
    int getStockQuantity();

    bool ajouter(); // Create
    QSqlQueryModel* afficher(); // Read
    bool modifier(QString vacid); // Update
    static bool supprimer(QString vacid); // Delete
};

#endif // VACCINE_H
