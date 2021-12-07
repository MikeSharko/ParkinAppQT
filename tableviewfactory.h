#ifndef TABLEVIEWFACTORY_H
#define TABLEVIEWFACTORY_H
#include <QtSql>
#include <QSqlDatabase>
#include "tableviewbase.h"
#include "tableviewlotA20.h"

class TableViewFactory
{
public:

    static TableViewBase* Create(int ID){
        switch (ID)
        {
        case 0:
            return new TableViewLot20;
        //case 1:
          //  return new TableViewLot20;
        default: return new TableViewLot20;
        }
    }
};

#endif // TABLEVIEWFACTORY_H
