#include "querytraindialog.h"
#include "ui_querytraindialog.h"
#include "addtraindialog.h"
#include <QMessageBox>

queryTrainDialog::queryTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryTrainDialog)
{
    ui->setupUi(this);
}

queryTrainDialog::~queryTrainDialog()
{
    delete ui;
}

void queryTrainDialog::on_confirmButton_clicked()
{
    QString train_id = ui->lineEdit->text();
    if (train_id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车号不能为空"));
        return;
    }
    addtrainDialog *addtraindialog = new addtrainDialog(parentWidget(), train_id);
    close();
    addtraindialog->exec();
}
