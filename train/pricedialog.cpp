#include "pricedialog.h"
#include "ui_pricedialog.h"
#include "addtraindialog.h"
#include <QPushButton>
#include <QMessageBox>

priceDialog::priceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::priceDialog)
{
    ui->setupUi(this);
}

priceDialog::~priceDialog()
{
    delete ui;
}

void priceDialog::getReadyPrice(QString name)
{
    ui->price_name->setText(name);
}

void priceDialog::setType(int kind)
{
    type = kind;
}

void priceDialog::on_pushButton_clicked()
{
    if(ui->price_name->text() == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入您的票价名称"));
        return;
    }
    if(type == 0) father->addprice(ui->price_name->text());
    else father->modifyprice(ui->price_name->text());
    close();
}
