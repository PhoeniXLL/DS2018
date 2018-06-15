#include "queryticketdialog.h"
#include "ui_queryticketdialog.h"
#include <QProcess>
#include <QMessageBox>
#include "buyticketdialog.h"

queryTicketDialog::queryTicketDialog(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::queryTicketDialog),
    id(_id)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(onCellDoubleClicked(int,int)));
}

queryTicketDialog::~queryTicketDialog()
{
    delete ui;
}

void queryTicketDialog::on_searchButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    loc1 = ui->lineEdit_1->text();
    if (loc1 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入始发地"));
    }
    loc2 = ui->lineEdit_2->text();
    if (loc2 == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入目的地"));
    }
    date = ui->dateEdit->date().toString(Qt::ISODate);
    catalog = ui->lineEdit_3->text();
    if (catalog == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入列车种类"));
    }

    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "query_ticket " + loc1 + " " + loc2 + " " + date + " " + catalog + "\n";
    //qDebug() << command;
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    QString ret = QString(backend.readAllStandardOutput());
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    //qDebug() << ret;
    if (ret == "-1\r\n") {
        QMessageBox::information(this, trUtf8("错误"), trUtf8("查询不到此种类的票"));
        return;
    }
    ui->tableWidget->setColumnCount(22);
    QStringList header;
    header << trUtf8("列车号") << trUtf8("始发地") << trUtf8("出发日期") << trUtf8("出发时间") << trUtf8("目的地") << trUtf8("到达日期") << trUtf8("到达时间");
    for (int i = 1; i <= 5; i++) {
        header << QString("票价种类(%1)").arg(i)
               << QString("剩余票数(%1)").arg(i)
               << QString("价格(%1)").arg(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(header);
    int listnum = ret.section('\r', 0, 0).toInt();
    for (int i = 0; i < listnum; i++) {
        QString ss = ret.section('\r', 1 + i, 1 + i).section('\n', 1, 1);
        ui->tableWidget->insertRow(i);
        for (int j = 0; ss != ""; j++) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(ss.section(' ', 0, 0)));
            ss = ss.section(' ', 1);
            //qDebug() << ss;
        }
    }
}

void queryTicketDialog::onCellDoubleClicked(int row, int column)
{
    QString data = ui->tableWidget->item(row, 0)->text() + " " + loc1 + " " + loc2 + " "
                   + ui->tableWidget->item(row, 2)->text() + " ";
    if (column >= 7 && ui->tableWidget->item(row, column - (column - 7) % 3) != NULL) {
        data += ui->tableWidget->item(row, column - (column - 7) % 3)->text();
    }
    buyTicketDialog *buyticketdialog = new buyTicketDialog(this, id, data);
    buyticketdialog->exec();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "query_ticket " + loc1 + " " + loc2 + " " + date + " " + catalog + "\n";
    //qDebug() << command;
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    QString ret = QString(backend.readAllStandardOutput());
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    //qDebug() << ret;
    if (ret == "-1\r\n") {
        QMessageBox::information(this, trUtf8("错误"), trUtf8("查询不到此种类的票"));
        return;
    }
    ui->tableWidget->setColumnCount(22);
    QStringList header;
    header << trUtf8("列车号") << trUtf8("始发地") << trUtf8("出发日期") << trUtf8("出发时间") << trUtf8("目的地") << trUtf8("到达日期") << trUtf8("到达时间");
    for (int i = 1; i <= 5; i++) {
        header << QString("票价种类(%1)").arg(i)
               << QString("剩余票数(%1)").arg(i)
               << QString("价格(%1)").arg(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(header);
    int listnum = ret.section('\r', 0, 0).toInt();
    for (int i = 0; i < listnum; i++) {
        QString ss = ret.section('\r', 1 + i, 1 + i).section('\n', 1, 1);
        ui->tableWidget->insertRow(i);
        for (int j = 0; ss != ""; j++) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(ss.section(' ', 0, 0)));
            ss = ss.section(' ', 1);
            //qDebug() << ss;
        }
    }
}
