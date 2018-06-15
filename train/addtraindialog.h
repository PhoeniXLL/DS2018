#ifndef ADDTRAINDIALOG_H
#define ADDTRAINDIALOG_H

#include <QDialog>
#include "pricedialog.h"
#include "stationdialog.h"

namespace Ui {
class addtrainDialog;
}

class addtrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addtrainDialog(QWidget *parent = 0, QString _train_id = "");
    ~addtrainDialog();
    void addprice(QString);
    void modifyprice(QString);
    void addStation(QStringList);
    void modifyStation(QStringList);

private slots:
    void on_addButton_1_clicked();

    void on_delButton_1_clicked();

    void on_modifyButton_1_clicked();

    void on_addButton_2_clicked();

    void on_delButton_2_clicked();

    void on_modifyButton_2_clicked();

    void on_comfirmButton_clicked();

private:
    Ui::addtrainDialog *ui;
    priceDialog *now_price;
    stationDialog *now_station;
    QString train_id;
};

#endif // ADDTRAINDIALOG_H
