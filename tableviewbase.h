#ifndef TABLEVIEWBASE_H
#define TABLEVIEWBASE_H

#include <QObject>
#include <QWidget>
#include <QtSql>

class TableViewBase
{
public:
    virtual void createTableView() = 0;


};

#endif // TABLEVIEWBASE_H
