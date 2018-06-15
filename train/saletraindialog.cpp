#include "saletraindialog.h"
#include "ui_saletraindialog.h"
#include <QProcess>
#include <QMessageBox>

saleTrainDialog::saleTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saleTrainDialog)
{
    ui->setupUi(this);
}

saleTrainDialog::~saleTrainDialog()
{
    delete ui;
}

void saleTrainDialog::on_confirmButton_clicked()
{
    QString train_id = ui->lineEdit->text();
    if (train_id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入要公开的列车号"));
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "sale_train " + train_id + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        QMessageBox::information(this, trUtf8("成功"), trUtf8("公开成功"));
        close();
    } else {
        ui->lineEdit->clear();
        QMessageBox::information(this, trUtf8("错误"), trUtf8("公开失败"));
    }
}
