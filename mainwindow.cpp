#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //placeholders for login tab
    ui->loginUsername->setPlaceholderText("Enter your Username");
    ui->loginPassword->setPlaceholderText("Enter your Password");


    //placeholders for register tab
    ui->registerUsername->setPlaceholderText("Define your Username");
    ui->registerPassword->setPlaceholderText("Define your password");
    ui->registerEmail->setPlaceholderText("Enter your Email");


}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//do not delete this func
}


void MainWindow::on_registerBtn_clicked()
{
    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");

    if (db.open()) {
        //getting information from fields and storing into varibles
    QString username = ui->registerUsername->text();
    QString password = ui->registerPassword->text();
    QString email    = ui->registerEmail->text();

    //Run isert Query

    QSqlQuery qry;
    qry.prepare("INSERT INTO USERS(username, password, email)"
                "VALUES (:username, :password, :email)");
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);
    qry.bindValue(":email", email);
        if(qry.exec()){
             QMessageBox::information(this, "Inserted", "Inserted successfully");
            }
        else{
            QMessageBox::information(this, "Not Inserted", "Not Inserted");
            }
     }
     else
     {
        QMessageBox::information(this, "Not Connected", "Database is not connected");
     }
    db.close();

}


void MainWindow::on_loginBtn_clicked()
{
    //connection to MYSQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Parking/Db/mydb.sqlite");
//"C:/Users/Xcom/Documents/Parking/Db/mydb.sqlite"
    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();
    if(db.open()){

        //creating queries
        QSqlQuery query(QSqlDatabase::database("USERS"));
        query.prepare(QString("SELECT * FROM USERS WHERE username=:username AND password = :password"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if(!query.exec()){
            QMessageBox::information(this, "Faild", "Query failed");
        }
        else {
            while(query.next()){
                QString usernameFromDb = query.value(1).toString();
                QString passwordFromDb = query.value(2).toString();
                if(usernameFromDb == username && passwordFromDb == password){
                    QMessageBox::information(this, "Success", "Login Success");

                    //redirecting to another dialog
//                     Dialog MainProgram;
//                     MainProgram.setModal(true);
//                     MainProgram.exec();

                     hide();
                     secondWindow = new Dialog(this);
                     secondWindow->show();


                }
                else{
                   QMessageBox::information(this, "Failed", "Login Failed");
                }
            }
        }

    }
    else{

         QMessageBox::information(this, "Not Connected", "Database is not connected");
    }
     db.close();
}

