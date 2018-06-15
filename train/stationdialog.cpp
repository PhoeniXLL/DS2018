#include "stationdialog.h"
#include "ui_stationdialog.h"
#include "addtraindialog.h"
#include <QPushButton>
#include <QMessageBox>

stationDialog::stationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stationDialog)
{
    ui->setupUi(this);
    ui->arriveBox->setCheckState(Qt::Checked);
    ui->startBox->setCheckState(Qt::Checked);
    ui->timearrive->setEnabled(true);
    ui->timestart->setEnabled(true);
    pricelabel[0] = ui->pricelabel_0;
    pricelabel[1] = ui->pricelabel_1;
    pricelabel[2] = ui->pricelabel_2;
    pricelabel[3] = ui->pricelabel_3;
    pricelabel[4] = ui->pricelabel_4;
//  pricelabel[5] = ui->pricelabel_5;
    pricebox[0] = ui->priceBox_0;
    pricebox[1] = ui->priceBox_1;
    pricebox[2] = ui->priceBox_2;
    pricebox[3] = ui->priceBox_3;
    pricebox[4] = ui->priceBox_4;
//  pricebox[5] = ui->priceBox_5;
}

stationDialog::~stationDialog()
{
    delete ui;
}

void stationDialog::setType(int kind)
{
    type = kind;
}

void stationDialog::getReadyStation(QStringList list)
{
    if(list.at(0) != "--") ui->nameEdit->setText(list.at(0));
    if(list.at(1) != "xx:xx") ui->timearrive->setTime(QTime::fromString(list.at(1), "hh:mm"));
    if(list.at(2) != "xx:xx") ui->timestart->setTime(QTime::fromString(list.at(2), "hh:mm"));
    ui->timestopover->setTime(QTime::fromString(list.at(3), "hh:mm"));
    for(int i = 4 ; i < 4 + pricenum ; ++ i) {
        QString price = list.at(i);
        pricebox[i - 4]->setValue(price.toDouble());
    }
}

void stationDialog::getReadyPrice(QStringList list)
{
    pricenum = list.size();
    for(int i = 0 ; i < list.size() ; ++ i) {
        pricelabel[i]->setText(list.at(i));
    }
    for(int i = list.size() ; i < 5 ; ++ i) {
        pricelabel[i]->setVisible(false);
        pricebox[i]->setVisible(false);
    }
}

void stationDialog::on_arriveBox_stateChanged(int arg1)
{
    //qDebug() << ui->timearrive->time().toString("hh:mm");
    if(arg1 == 0) ui->timearrive->setEnabled(false);
    else ui->timearrive->setEnabled(true);
}

void stationDialog::on_startBox_stateChanged(int arg1)
{
    if(arg1 == 0) ui->timestart->setEnabled(false);
    else ui->timestart->setEnabled(true);
}

void stationDialog::on_okButton_clicked()
{
    QString arrivetime = "xx:xx", starttime = "xx:xx";
    if(ui->arriveBox->checkState() == Qt::Checked) arrivetime = ui->timearrive->time().toString("hh:mm");
    if(ui->startBox->checkState() == Qt::Checked) starttime = ui->timestart->time().toString("hh:mm");
    QStringList list;
    if(ui->nameEdit->text() == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入车站名称"));
        return;
    } else list << ui->nameEdit->text();

    list << arrivetime << starttime << ui->timestopover->time().toString("hh:mm");
    for(int i = 4 ; i < 4 + pricenum ; ++ i) {
        list << pricebox[i - 4]->text();
    }

    if(type == 0) {
        father->addStation(list);
    } else {
        father->modifyStation(list);
    }
    close();
}
