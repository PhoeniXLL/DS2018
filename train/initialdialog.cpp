#include "initialdialog.h"
#include "ui_initialdialog.h"
#include "logindialog.h"
#include "registerdialog.h"

initialDialog::initialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initialDialog)
{
    ui->setupUi(this);
}

initialDialog::~initialDialog()
{
    delete ui;
}

void initialDialog::on_loginButton_clicked()
{
    loginDialog *logindialog = new loginDialog();
    logindialog->show();
    close();
}

void initialDialog::on_registerButton_clicked()
{
    registerDialog *registerdialog = new registerDialog();
    registerdialog->show();
    close();
}
