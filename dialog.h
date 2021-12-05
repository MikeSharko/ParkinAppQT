#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QtDebug>
#include <QMessageBox>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void update();

    void on_logoutBtn_clicked();

private:
    Ui::Dialog *ui;
    QSqlQueryModel *querymodel;
    QSqlQueryModel *querymodel2;
};

#endif // DIALOG_H


