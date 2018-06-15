#include "deletetraindialog.h"
#include "ui_deletetraindialog.h"
#include <QProcess>
#include <QMessageBox>

deleteTrainDialog::deleteTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteTrainDialog)
{
    ui->setupUi(this);
}

deleteTrainDialog::~deleteTrainDialog()
{
    delete ui;
}

void deleteTrainDialog::on_confirmButton_clicked()
{
    QString train_id = ui->lineEdit->text();
    if (train_id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入列车号"));
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "delete_train " + train_id + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        QMessageBox::information(this, trUtf8("成功"), trUtf8("删除成功"));
        close();
    } else {
        ui->lineEdit->clear();
        QMessageBox::information(this, trUtf8("错误"), trUtf8("删除失败"));
    }
}
