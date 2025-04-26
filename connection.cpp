#include "connection.h"

Connection::Connection() {}
bool Connection::createConnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_ProjetA2");
    db.setUserName("vaccination");
    db.setPassword("vaccination");
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){
    db.close();
}
