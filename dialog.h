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
     void showOpenSlots();
     void updateTimeOnUI();
     void updateLotFreeSpace();
     void clearAllSpotsAt10pm();
     void updateParkingInfo();

    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void update();

    void on_logoutBtn_clicked();

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::Dialog *ui;
    QSqlQueryModel *querymodel;
    QSqlQueryModel *querymodel2;
};

#endif // DIALOG_H


