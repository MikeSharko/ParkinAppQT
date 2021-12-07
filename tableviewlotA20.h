#ifndef TABLEVIEWLOTA20_H
#define TABLEVIEWLOTA20_H

#include <QObject>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "tableviewbase.h"
#include <iostream>
#include <QtDebug>
#include <QDialog>




class TableViewLot20: public TableViewBase
{
public:

    void createTableView();





private:
QSqlQueryModel *querymodel;


};
#endif // TABLEVIEWLOTA20_H
