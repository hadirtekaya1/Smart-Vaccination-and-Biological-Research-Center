#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>


class Connection
{
public:
    Connection();
    bool createconnect();
};

#endif // CONNECTION_H
