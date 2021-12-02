#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

//global variables
int maxCapacityA = 20; //we decided to have maximum of 20 spots in each parking lot for simplicity
float progressBarValueA;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


   // QDateTime dt = QDateTime::currentDateTime();
    //dt.setTime(QTime());

   QTime time = QTime::currentTime();

   // Qstring buttnValue = button->text();
    //QString::compare(buttnValue, "+" Qt::CaseInsesative == 0);


   // this QVariant converts any data type to string
   QString m =  QVariant(time).toString();
   ui->timeLabel->setText(m);





    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
     if (db.open()) {
         querymodel = new QSqlTableModel();//QSqlQueryModel();
        querymodel->setTable("LOTA");
      querymodel->select();
       ui->tableView->setModel(querymodel);

         QSqlQuery qry;
         qry.prepare("SELECT reservedFrom, reservedTo FROM LOTA");
         if(qry.exec()){
             while(qry.next()){
                  QString from = qry.value(0).toString();
                  QString to = qry.value(1).toString();
             }
         }




         //int col = ui->tableView->currentIndex().column();
      //   int row = ui->tableView->currentIndex().row();


         //setting a progressbar value
         progressBarValueA = querymodel->rowCount();
         progressBarValueA = (progressBarValueA/maxCapacityA) *100;
         ui->progressBarA->setValue(progressBarValueA);

        // querymodel2 = new QSqlQueryModel();
        // querymodel2->setQuery("SELECT * FROM LOTB");
        // ui->tableView_2->setModel(querymodel2);
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
    QString reservedFrom  = ui->timeAfrom->text();
    QString reservedTo    = ui->timeAto->text();

    //Run isert Query

    QSqlQuery qry;
    qry.prepare("INSERT INTO LOTA(slot, reservedFrom, reservedTo)"
                "VALUES (:slot, :reservedFrom, :reservedTo)");
    qry.bindValue(":slot", slot);
    qry.bindValue(":reservedFrom", reservedFrom);
    qry.bindValue(":reservedTo", reservedTo);
        if(qry.exec()){

             QMessageBox::information(this, "Inserted", "Inserted successfully");

             querymodel->select();
             ui->tableView->setModel(querymodel);

             //setting a progressbar value
             progressBarValueA = querymodel->rowCount();
             progressBarValueA = (progressBarValueA/maxCapacityA) *100;
             ui->progressBarA->setValue(progressBarValueA);
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

