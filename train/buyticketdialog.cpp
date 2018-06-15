#include "buyticketdialog.h"
#include "ui_buyticketdialog.h"
#include <QProcess>
#include <QMessageBox>

buyTicketDialog::buyTicketDialog(QWidget *parent, int _id, QString data) :
    QDialog(parent),
    ui(new Ui::buyTicketDialog),
    id(_id)
{
    ui->setupUi(this);
    if (id) {
        ui->lineEdit_1->setText(QString::number(id));
        ui->lineEdit_1->setFocusPolicy(Qt::NoFocus);
    }
    if (data != "") {
        ui->lineEdit_3->setText(data.section(' ', 0, 0));
        ui->lineEdit_3->setFocusPolicy(Qt::NoFocus);
        ui->lineEdit_4->setText(data.section(' ', 1, 1));
        ui->lineEdit_4->setFocusPolicy(Qt::NoFocus);
        ui->lineEdit_5->setText(data.section(' ', 2, 2));
        ui->lineEdit_5->setFocusPolicy(Qt::NoFocus);
        ui->dateEdit->setDate(QDate(data.section(' ', 3, 3).section('-', 0, 0).toInt(),
                                    data.section(' ', 3, 3).section('-', 1, 1).toInt(),
                                    data.section(' ', 3, 3).section('-', 2, 2).toInt()));
        ui->dateEdit->setFocusPolicy(Qt::NoFocus);
        if (data.section(' ', 4, 4) != "") {
            ui->lineEdit_7->setText(data.section(' ', 4, 4));
            ui->lineEdit_7->setFocusPolicy(Qt::NoFocus);
       }
    }
}

buyTicketDialog::~buyTicketDialog()
{
    delete ui;
}

void buyTicketDialog::on_confirmButton_clicked()
{
    QString id = ui->lineEdit_1->text();
    QString num = QString::number(ui->spinBox->value());
    QString train_id = ui->lineEdit_3->text();
    QString loc1 = ui->lineEdit_4->text();
    QString loc2 = ui->lineEdit_5->text();
    QString date = ui->dateEdit->date().toString(Qt::ISODate);
    QString ticket_kind = ui->lineEdit_7->text();
    if (id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("用户id不应为空"));
        return;
    }
    if (num == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("购票数量不应为空"));
        return;
    }
    if (train_id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车号不应为空"));
        return;
    }
    if (loc1 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("始发地不应为空"));
        return;
    }
    if (loc2 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("目的地不应为空"));
        return;
    }
    if (ticket_kind == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("票价种类不应为空"));
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "buy_ticket " + id + " " + num + " " + train_id + " " + loc1 + " " + loc2 + " " + date + " " + ticket_kind + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        QMessageBox::information(this, trUtf8("成功"), trUtf8("购票成功"));
        close();
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("购票失败"));
        if (!this->id) {
            ui->lineEdit_1->clear();
        }
        ui->spinBox->setValue(1);
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->dateEdit->setDate(QDate(2018, 6, 1));
        ui->lineEdit_7->clear();
        return;
    }
}
