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


void Dialog::update(){
    //QMessageBox::information(this, "Update", "Update");


    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
    QTime time = QTime::currentTime();
    QString m = time.toString("h AP");

    if (db.open()) {

        //UPDATING the table view
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT slot, reservedFrom, reservedTo, parked FROM LOTA");
        ui->tableView->setModel(querymodel);



        //querymodel->setTable("LOTA");
        //querymodel->select();
        //ui->tableView->setModel(querymodel);



        //UPDATING current time for user

        QString labeltime = time.toString("h : mm AP");
        ui->timeLabel->setText(labeltime);





        QSqlQuery qry;
        QSqlQuery subQuery;
        qry.prepare("SELECT slot, reservedFrom, reservedTo FROM LOTA");
        if(qry.exec()){
            while(qry.next()){
                QString slot = qry.value(0).toString();
                QString reservedfrom = qry.value(1).toString();
                QString reservedto = qry.value(2).toString();
                if(reservedfrom == m ){
                   // QMessageBox::information(this, "YEP", "YEP");
                    subQuery.prepare("UPDATE LOTA SET parked='parked' WHERE slot='"+slot+"'  ");
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

             querymodel = new QSqlQueryModel();
             querymodel->setQuery("SELECT slot, reservedFrom, reservedTo, parked FROM LOTA");
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

