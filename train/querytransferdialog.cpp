#include "querytransferdialog.h"
#include "ui_querytransferdialog.h"
#include <QMessageBox>
#include <QProcess>

queryTransferDialog::queryTransferDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryTransferDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

queryTransferDialog::~queryTransferDialog()
{
    delete ui;
}

void queryTransferDialog::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);

    QString loc1 = ui->lineEdit_1->text();
    QString loc2 = ui->lineEdit_2->text();
    QString date = ui->dateEdit->date().toString(Qt::ISODate);
    QString catalog = ui->lineEdit_4->text();
    if (loc1 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("始发地不能为空"));
        return;
    }
    if (loc2 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("目的地不能为空"));
        return;
    }
    if (catalog == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车类别不能为空"));
        return;
    }

    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "query_transfer " + loc1 + " " + loc2 + " " + date + " " + catalog + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    QString ret = QString(backend.readAllStandardOutput());
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret == "-1\r\n") {
        QMessageBox::information(this, trUtf8("错误"), trUtf8("查询非法"));
        return;
    }

    QString ret1 = ret.section('\r', 0, 0);
    QString ret2 = ret.section('\n', 1, 1).section('\r', 0, 0);

    ui->tableWidget->setColumnCount(22);
    QStringList header;
    header << trUtf8("列车号") << trUtf8("始发地") << trUtf8("出发日期") << trUtf8("出发时间") << trUtf8("目的地") << trUtf8("到达日期") << trUtf8("到达时间");
    for (int i = 1; i <= 5; i++) {
        header << QString("票价种类(%1)").arg(i)
               << QString("剩余票数(%1)").arg(i)
               << QString("价格(%1)").arg(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(header);
    QString ss = ret1;
    for (int j = 0; ss != ""; j++) {
        ui->tableWidget->setItem(0, j, new QTableWidgetItem(ss.section(' ', 0, 0)));
        ss = ss.section(' ', 1);
    }

    ss = ret2;
    for (int j = 0; ss != ""; j++) {
        ui->tableWidget->setItem(1, j, new QTableWidgetItem(ss.section(' ', 0, 0)));
        ss = ss.section(' ', 1);
    }
}
