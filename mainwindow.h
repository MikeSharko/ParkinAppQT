#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QtDebug>
#include "dialog.h"
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_registerBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    Dialog *secondWindow;

};
#endif // MAINWINDOW_H


