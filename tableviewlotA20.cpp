#include "tableviewlotA20.h"
#include "dialog.h"
#include "ui_dialog.h"





void TableViewLot20::createTableView()
{

     qDebug() << "CreateViewLot20 called";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    querymodel = new QSqlQueryModel;
    db.setDatabaseName("../ParkinAppQT/Db/mydb.sqlite");
    if (db.open()) {
        querymodel->setQuery("SELECT slot, reservedFrom, reservedTo, parked, username FROM LOTA");
        //ui->tableView->setModel(querymodel);

    }
}


