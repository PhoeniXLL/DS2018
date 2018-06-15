#include "modifyprofiledialog.h"
#include "ui_modifyprofiledialog.h"
#include <QProcess>
#include <QMessageBox>

modifyProfileDialog::modifyProfileDialog(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::modifyProfileDialog),
    id(_id)
{
    ui->setupUi(this);
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "query_profile " + QString::number(id) + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    QString ret = QString(backend.readAllStandardOutput());
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    ui->lineEdit_1->setText(ret.section(' ', 0, 0));
    ui->lineEdit_5->setText(ret.section(' ', 1, 1));
    ui->lineEdit_6->setText(ret.section(' ', 2, 2));
}

modifyProfileDialog::~modifyProfileDialog()
{
    delete ui;
}

void modifyProfileDialog::on_applyButton_clicked()
{
    QString name = ui->lineEdit_1->text();
    QString password = ui->lineEdit_2->text();
    if (password == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入你的密码"));
        return;
    }
    QString new_password = ui->lineEdit_3->text();
    QString confirm_new_password = ui->lineEdit_4->text();
    QString email = ui->lineEdit_5->text();
    QString phone = ui->lineEdit_6->text();

    if (name == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("用户名不能为空"));
        return;
    }
    if (email == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("电子邮箱不能为空"));
        return;
    }
    if (phone == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("电话号码不能为空"));
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "login " + QString::number(id) + " " + password + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        if (new_password != "" && new_password != confirm_new_password) {
            QMessageBox::critical(this, trUtf8("错误"), trUtf8("两次新密码输入不一致"));
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            return;
        }
        QProcess backend;
        backend.start("backend.exe");
        backend.waitForStarted();
        QString command = "modify_profile " + QString::number(id) + " " + name + " "
                          + (new_password == "" ? password : new_password) + " " + email + " " + phone + "\n";
        backend.write(command.toStdString().c_str());
        backend.waitForReadyRead();
        int ret = QString(backend.readAllStandardOutput()).toInt();
        backend.write("exit\n");
        backend.waitForFinished();
        backend.close();
        if (ret) {
            QMessageBox::information(this, trUtf8("成功"), trUtf8("修改成功"));
            close();
        } else {
            QMessageBox::information(this, trUtf8("错误"), trUtf8("修改失败"));
            ui->lineEdit_1->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
        }
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("密码错误"));
        ui->lineEdit_2->clear();
    }
}
