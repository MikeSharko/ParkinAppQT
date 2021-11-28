#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

//global variables
int maxCapacity = 20; //we decided to have maximum of 20 spots in each parking lot for simplicity
float progressBarValue;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
     if (db.open()) {
         querymodel = new QSqlQueryModel();
         querymodel->setQuery("SELECT * FROM LOTA");
         ui->tableView->setModel(querymodel);


         //setting a progressbar value
         progressBarValue = querymodel->rowCount();
         progressBarValue = (progressBarValue/maxCapacity) *100;
         ui->progressBarA->setValue(progressBarValue);

         querymodel2 = new QSqlQueryModel();
         querymodel2->setQuery("SELECT * FROM LOTB");
         ui->tableView_2->setModel(querymodel2);
     }





}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");


    if (db.open()) {
    //getting information from fields and storing into varibles
    QString slot        = ui->slotA->text();
    QString parkedFrom  = ui->timeAfrom->text();
    QString parkedTo    = ui->timeAto->text();

    //Run isert Query

    QSqlQuery qry;
    qry.prepare("INSERT INTO LOTA(slot, parkedFrom, parkedTo)"
                "VALUES (:slot, :parkedFrom, :parkedTo)");
    qry.bindValue(":slot", slot);
    qry.bindValue(":parkedFrom", parkedFrom);
    qry.bindValue(":parkedTo", parkedTo);
        if(qry.exec()){
             QMessageBox::information(this, "Inserted", "Inserted successfully");
             querymodel->setQuery("SELECT * FROM LOTA");

             //setting a progressbar value
             progressBarValue = querymodel->rowCount();
             progressBarValue = (progressBarValue/maxCapacity) *100;
             ui->progressBarA->setValue(progressBarValue);
            }
        else{
            QMessageBox::information(this, "Not Inserted", "Slot is occupied");
            }
     }
     else
     {
        QMessageBox::information(this, "Not Connected", "Database is not connected");
     }
    db.close();


}

