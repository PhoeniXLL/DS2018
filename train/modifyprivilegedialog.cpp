#include "modifyprivilegedialog.h"
#include "ui_modifyprivilegedialog.h"
#include <QProcess>
#include <QMessageBox>

modifyPrivilegeDialog::modifyPrivilegeDialog(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::modifyPrivilegeDialog),
    id(_id)
{
    ui->setupUi(this);
}

modifyPrivilegeDialog::~modifyPrivilegeDialog()
{
    delete ui;
}

void modifyPrivilegeDialog::on_confirmButton_clicked()
{
    QString id2 = ui->lineEdit->text();
    if (id2 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入要升为管理员的用户id"));
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "modify_privilege " + QString::number(id) + " " + id2 + " 2\n";
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
        ui->lineEdit->clear();
        QMessageBox::information(this, trUtf8("错误"), trUtf8("修改失败"));
    }
}
