#include "connection.h"


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_ProjetA2");//inserer le nom de la source de données
    db.setUserName("vaccination");//inserer nom de l'utilisateur
    db.setPassword("vaccination");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}
