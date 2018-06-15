#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include <QProcess>
#include "initialdialog.h"

registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_registerButton_clicked()
{
    QString name = ui->lineEdit_1->text();
    QString password = ui->lineEdit_2->text();
    QString confirm_password = ui->lineEdit_3->text();
    QString email = ui->lineEdit_4->text();
    QString phone = ui->lineEdit_5->text();
    if (name == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("用户名不应为空"));
        return;
    }
    if (password == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("密码不应为空"));
        return;
    }
    if (confirm_password == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请确认密码"));
        return;
    }
    if (email == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("电子邮箱不应为空"));
        return;
    }
    if (phone == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("电话号码不应为空"));
        return;
    }
    if (password != confirm_password) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("两次密码输入不一致"));
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "register " + name + " " + password + " " + email + " " + phone + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        QString information = "注册成功，你的id为" + QString::number(ret);
        QMessageBox::information(this, trUtf8("成功"), information);
        close();
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("注册失败"));
        ui->lineEdit_1->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        return;
    }
}

void registerDialog::closeEvent(QCloseEvent *event)
{
    initialDialog *initialdialog = new initialDialog();
    initialdialog->show();
}
