#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QByteArray>

class Patient {
private:
    QString FIRST_NAME;
    QString LAST_NAME;
    QString GENDER;
    QDate DATE_OF_BIRTH;
    QString ADDRESS;
    QString EMAIL;
    QString PHONE_NUMBER;

    // Helper functions for QR generation

public:
    Patient();
    Patient(QString, QString, QString, QDate, QString, QString, QString);

    QString getFirstname();
    QString getLastname();
    QString getGender();
    QDate getDateofbirth();
    QString getAddress();
    QString getEmail();
    QString getPhonenumber();


    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(QString PATIENT_ID);
    static bool supprimer(QString PATIENT_ID);
};

#endif // PATIENT_H
