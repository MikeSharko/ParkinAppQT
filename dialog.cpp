#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <string>
//global variables
int maxCapacityA = 20; //we decided to have maximum of 20 spots in each parking lot for simplicity
float progressBarValueA;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);



    // this QVariant converts any data type to string
    //QString m =  QVariant(time).toString();
     QTime time = QTime::currentTime();
     QString m = time.toString("h : mm AP");
    ui->timeLabel->setText(m);


    //this will call a function update() every 3 seconds
    //in function Update is the main ENGINE of the parking reserve
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(3000);




    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
    if (db.open()) {
        querymodel = new QSqlTableModel();//QSqlQueryModel();
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT slot, reservedFrom, reservedTo, parked FROM LOTA");
        ui->tableView->setModel(querymodel);




        //this query calculates the number of reserved places in a LOT( we need this to calculate the % occupied)
        QSqlQuery qry;
        qry.prepare("SELECT reservedFrom FROM LOTA");
        int a=0;
        if(qry.exec()){

            while(qry.next()){
                QString dbSlot = qry.value(0).toString();
                if(dbSlot!=""){
                  a++;
                }


            }
        }
        //setting a progressbar value
        progressBarValueA = a;
        progressBarValueA = (progressBarValueA/maxCapacityA) *100;
        ui->progressBarA->setValue(progressBarValueA);

        // querymodel2 = new QSqlQueryModel();
        // querymodel2->setQuery("SELECT * FROM LOTB");
        // ui->tableView_2->setModel(querymodel2);
    }
    db.close();
}

Dialog::~Dialog()
{
    delete ui;
}




//WHERE THE MAIN ENGINE WORKS
void Dialog::update(){
    //QMessageBox::information(this, "Update", "Update");


    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
    QTime time = QTime::currentTime();
    QString currentTime = time.toString("h AP");

    //if time  >10 PM erase the DB
    if (db.open()){
        if(currentTime == "10 PM" || currentTime == "11 PM"){
            QSqlQuery query;
            query.prepare("UPDATE LOTA SET reservedFrom='', reservedTo='', parked='' WHERE slot IN (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20) ");
            if (query.exec()){

            }
            else{QMessageBox::information(this, "not Execute", "Query is not Executed");}
        }
    }




    if (db.open()) {

        //UPDATING the table view
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT slot, reservedFrom, reservedTo, parked FROM LOTA");
        ui->tableView->setModel(querymodel);


        //UPDATING current time for user

        QString labeltime = time.toString("h : mm AP");
        ui->timeLabel->setText(labeltime);



        //this query calculates the number of reserved places in a LOT( we need this to calculate the % occupied)
        QSqlQuery qry;
        qry.prepare("SELECT reservedFrom FROM LOTA");
        int a=0;
        if(qry.exec()){

            while(qry.next()){
                QString dbSlot = qry.value(0).toString();
                if(dbSlot!=""){
                    a++;
                }


            }
        }

        //setting a progressbar value
        progressBarValueA = a;
        progressBarValueA = (progressBarValueA/maxCapacityA) *100;
        ui->progressBarA->setValue(progressBarValueA);



        QSqlQuery subQuery;
        qry.prepare("SELECT slot, reservedFrom, reservedTo FROM LOTA");
        if(qry.exec()){
            while(qry.next()){
                QString dbSlot = qry.value(0).toString();
                QString dbReservedfrom = qry.value(1).toString();
                QString dbReservedto = qry.value(2).toString();
                if(dbReservedfrom == currentTime ){
                    // QMessageBox::information(this, "YEP", "YEP");
                    subQuery.prepare("UPDATE LOTA SET parked='parked' WHERE slot='"+dbSlot+"'  ");
                    subQuery.exec();
                }
                else if (dbReservedto == currentTime ){
                    subQuery.prepare("UPDATE LOTA SET parked='', reservedFrom='', reservedTo='' WHERE slot='"+dbSlot+"'  ");
                    subQuery.exec();
                }
            }

        }
    }//if db.open end fuction
}




void Dialog::on_pushButton_clicked()
{
    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
     QTime time = QTime::currentTime();
     QString currentTime = time.toString("h AP");
    QString uiSlot          = ui->slotA->text();
    QString uiReservedFrom  = ui->timeAfrom->text();
    QString uiReservedTo    = ui->timeAto->text();



    if (db.open()) {
        //getting information from fields and storing into varibles

        QSqlQuery qry;
        QSqlQuery subQuery;

        qry.prepare("SELECT slot, reservedFrom, reservedTo FROM LOTA");
        if(qry.exec()){
            while(qry.next()){
                QString dbSlot = qry.value(0).toString();
                QString dbReservedfrom = qry.value(1).toString();
                QString dbReservedto = qry.value(2).toString();

                //ONLY if the current slot is not occupied
                if(dbReservedfrom == "" && dbSlot == uiSlot){

                    //User can only updte the slot(database) he can not add a new slot
                    subQuery.prepare("UPDATE LOTA SET reservedFrom='"+uiReservedFrom+"', reservedTo='"+uiReservedTo+"' WHERE slot='"+uiSlot+"'  " );
                    subQuery.exec();
                    QMessageBox::information(this, "Reserved", "Reserved successfully");


                }
                else if(uiSlot == dbSlot){
                     QMessageBox::information(this, "Occupied", "Sorry current slot Reserved");

                    }

            }

        }

        else
        {
            QMessageBox::information(this, "Not Connected", "Database is not connected");
        }

    }



}


