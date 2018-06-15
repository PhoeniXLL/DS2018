#include "userdialog.h"
#include "ui_userdialog.h"
#include <QMessageBox>
#include "modifyprofiledialog.h"
#include "initialdialog.h"
#include "buyticketdialog.h"
#include "refundticketdialog.h"
#include "querytransferdialog.h"
#include "modifytraindialog.h"
#include "queryticketdialog.h"
#include "queryorderdialog.h"

userDialog::userDialog(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::userDialog),
    id(_id)
{
    ui->setupUi(this);
}

userDialog::~userDialog()
{
    delete ui;
}

void userDialog::on_logoutButton_clicked()
{
    int ret = QMessageBox::question(this, trUtf8("提醒"), trUtf8("你确定吗？"), QMessageBox::Yes, QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        close();
    }
}

void userDialog::on_modifyProfileButton_clicked()
{
    modifyProfileDialog *modifyprofiledialog = new modifyProfileDialog(this, id);
    modifyprofiledialog->exec();
}

void userDialog::closeEvent(QCloseEvent *event)
{
    initialDialog *initialdialog = new initialDialog();
    initialdialog->show();
}

void userDialog::on_buyTicketButton_clicked()
{
    buyTicketDialog *buyticketdialog = new buyTicketDialog(this, id);
    buyticketdialog->exec();
}

void userDialog::on_refundTicketButton_clicked()
{
    refundTicketDialog *refundticketdialog = new refundTicketDialog(this, id);
    refundticketdialog->exec();
}

void userDialog::on_queryTransferButton_clicked()
{
    queryTransferDialog *querytransferdialog = new queryTransferDialog(this);
    querytransferdialog->exec();
}

void userDialog::on_queryTrainButton_clicked()
{
    modifyTrainDialog *modifytraindialog = new modifyTrainDialog(this);
    modifytraindialog->exec();
}

void userDialog::on_queryTicketButton_clicked()
{
    queryTicketDialog *queryticketdialog = new queryTicketDialog(this, id);
    queryticketdialog->exec();
}

void userDialog::on_queryOrderButton_clicked()
{
    queryOrderDialog *queryorderdialog = new queryOrderDialog(this, id);
    queryorderdialog->exec();
}
