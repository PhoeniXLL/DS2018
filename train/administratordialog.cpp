#include "administratordialog.h"
#include "ui_administratordialog.h"
#include <QMessageBox>
#include <QProcess>
#include "modifyprofiledialog.h"
#include "initialdialog.h"
#include "modifyprivilegedialog.h"
#include "buyticketdialog.h"
#include "refundticketdialog.h"
#include "saletraindialog.h"
#include "deletetraindialog.h"
#include "addtraindialog.h"
#include "querytraindialog.h"
#include "querytransferdialog.h"
#include "queryorderdialog.h"
#include "queryticketdialog.h"
#include "modifytraindialog.h"

administratorDialog::administratorDialog(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::administratorDialog),
    id(_id)
{
    ui->setupUi(this);
}

administratorDialog::~administratorDialog()
{
    delete ui;
}

void administratorDialog::on_logoutButton_clicked()
{
    int ret = QMessageBox::question(this, trUtf8("提醒"), trUtf8("你确定吗?"), QMessageBox::Yes, QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        close();
    }
}

void administratorDialog::on_cleanButton_clicked()
{
    int ret = QMessageBox::question(this, trUtf8("提醒"), trUtf8("你确定吗?"), QMessageBox::Yes, QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        QProcess backend;
        backend.start("backend.exe");
        backend.waitForStarted();
        backend.write("clean\n");
        backend.waitForReadyRead();
        int ret = QString(backend.readAllStandardOutput()).toInt();
        backend.write("exit\n");
        backend.waitForFinished();
        backend.close();
        if (ret == 1) {
            QMessageBox::information(this, trUtf8("成功"), trUtf8("清空数据库成功"));
            close();
        } else {
            QMessageBox::information(this, trUtf8("错误"), trUtf8("清空数据库失败"));
        }
    }
}

void administratorDialog::on_modifyProfileButton_clicked()
{
    modifyProfileDialog *modifyprofiledialog = new modifyProfileDialog(this, id);
    modifyprofiledialog->exec();
}

void administratorDialog::closeEvent(QCloseEvent *event)
{
    initialDialog *initialdialog = new initialDialog();
    initialdialog->show();
}

void administratorDialog::on_modifyPrivilegeButton_clicked()
{
    modifyPrivilegeDialog *modifyprivilegedialog = new modifyPrivilegeDialog(this, id);
    modifyprivilegedialog->exec();
}

void administratorDialog::on_buyTicketButton_clicked()
{
    buyTicketDialog *buyticketdialog = new buyTicketDialog(this);
    buyticketdialog->exec();
}

void administratorDialog::on_refundTicketButton_clicked()
{
    refundTicketDialog *refundticketdialog = new refundTicketDialog(this);
    refundticketdialog->exec();
}

void administratorDialog::on_saleTrainButton_clicked()
{
    saleTrainDialog *saletraindialog = new saleTrainDialog(this);
    saletraindialog->exec();
}

void administratorDialog::on_deleteTrainButton_clicked()
{
    deleteTrainDialog *deletetraindialog = new deleteTrainDialog(this);
    deletetraindialog->exec();
}

void administratorDialog::on_addTrainButton_clicked()
{
    addtrainDialog *addtraindialog = new addtrainDialog(this);
    addtraindialog->exec();
}

void administratorDialog::on_modifyTrainButton_clicked()
{
    queryTrainDialog *querytraindialog = new queryTrainDialog(this);
    querytraindialog->exec();
}

void administratorDialog::on_queryTrainButton_clicked()
{
    modifyTrainDialog *modifytraindialog = new modifyTrainDialog(this);
    modifytraindialog->exec();
}

void administratorDialog::on_queryTransferButton_clicked()
{
    queryTransferDialog *querytransferdialog = new queryTransferDialog(this);
    querytransferdialog->exec();
}

void administratorDialog::on_queryOrderButton_clicked()
{
    queryOrderDialog *queryorderdialog = new queryOrderDialog(this, id);
    queryorderdialog->exec();
}

void administratorDialog::on_queryTicketButton_clicked()
{
    queryTicketDialog *queryticketdialog = new queryTicketDialog(this);
    queryticketdialog->exec();
}
