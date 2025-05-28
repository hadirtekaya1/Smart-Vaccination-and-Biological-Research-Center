#include "patient.h"
#include "qsqlerror.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <QRandomGenerator>

Patient::Patient(QString FIRST_NAME, QString LAST_NAME, QString GENDER,
                 QDate DATE_OF_BIRTH, QString ADDRESS, QString EMAIL, QString PHONE_NUMBER) :
    FIRST_NAME(FIRST_NAME), LAST_NAME(LAST_NAME), GENDER(GENDER),
    DATE_OF_BIRTH(DATE_OF_BIRTH), ADDRESS(ADDRESS), EMAIL(EMAIL),
    PHONE_NUMBER(PHONE_NUMBER) {}

// Getters implementation
QString Patient::getFirstname() { return FIRST_NAME; }
QString Patient::getLastname() { return LAST_NAME; }
QString Patient::getGender() { return GENDER; }
QDate Patient::getDateofbirth() { return DATE_OF_BIRTH; }
QString Patient::getAddress() { return ADDRESS; }
QString Patient::getEmail() { return EMAIL; }
QString Patient::getPhonenumber() { return PHONE_NUMBER; }

// Database operations
bool Patient::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO PATIENTS (FIRST_NAME, LAST_NAME, GENDER, "
                  "DATE_OF_BIRTH, ADDRESS, EMAIL, PHONE_NUMBER) "
                  "VALUES (:FIRST_NAME, :LAST_NAME, :GENDER, "
                  ":DATE_OF_BIRTH, :ADDRESS, :EMAIL, :PHONE_NUMBER)");

    query.bindValue(":FIRST_NAME", FIRST_NAME);
    query.bindValue(":LAST_NAME", LAST_NAME);
    query.bindValue(":GENDER", GENDER);
    query.bindValue(":DATE_OF_BIRTH", DATE_OF_BIRTH);
    query.bindValue(":ADDRESS", ADDRESS);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":PHONE_NUMBER", PHONE_NUMBER);

    if(!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Failed to add patient: " + query.lastError().text());
        return false;
    }
    return true;
}

QSqlQueryModel* Patient::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT PATIENT_ID, FIRST_NAME, LAST_NAME, GENDER, "
                    "DATE_OF_BIRTH, ADDRESS, EMAIL, PHONE_NUMBER FROM PATIENTS");
    if(model->lastError().isValid()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Failed to load patients: " + model->lastError().text());
    }
    return model;
}

bool Patient::modifier(QString PATIENT_ID) {
    QSqlQuery query;
    query.prepare("UPDATE PATIENTS SET FIRST_NAME = :FIRST_NAME, LAST_NAME = :LAST_NAME, "
                  "GENDER = :GENDER, DATE_OF_BIRTH = :DATE_OF_BIRTH, "
                  "ADDRESS = :ADDRESS, EMAIL = :EMAIL, PHONE_NUMBER = :PHONE_NUMBER "
                  "WHERE PATIENT_ID = :PATIENT_ID");

    query.bindValue(":PATIENT_ID", PATIENT_ID);
    query.bindValue(":FIRST_NAME", FIRST_NAME);
    query.bindValue(":LAST_NAME", LAST_NAME);
    query.bindValue(":GENDER", GENDER);
    query.bindValue(":DATE_OF_BIRTH", DATE_OF_BIRTH);
    query.bindValue(":ADDRESS", ADDRESS);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":PHONE_NUMBER", PHONE_NUMBER);

    if(!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Failed to update patient: " + query.lastError().text());
        return false;
    }
    return true;
}

bool Patient::supprimer(QString PATIENT_ID) {
    QSqlQuery query;
    query.prepare("DELETE FROM PATIENTS WHERE PATIENT_ID = :PATIENT_ID");
    query.bindValue(":PATIENT_ID", PATIENT_ID);

    if(!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Failed to delete patient: " + query.lastError().text());
        return false;
    }
    return true;
}
