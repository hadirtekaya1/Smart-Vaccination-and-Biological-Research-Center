#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createConnection(); // Établir la connexion

    MainWindow w;
    if(test) // Si la connexion est établie
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connexion réussite.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else // Si la connexion a échoué
    {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connexion échouée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    return a.exec();
}
