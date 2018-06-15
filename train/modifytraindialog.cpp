#include "modifytraindialog.h"
#include "ui_modifytraindialog.h"
#include <QMessageBox>
#include <QProcess>

modifyTrainDialog::modifyTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyTrainDialog)
{
    ui->setupUi(this);
}

modifyTrainDialog::~modifyTrainDialog()
{
    delete ui;
}

void modifyTrainDialog::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);

    QString train_id = ui->train_idLineEdit->text();
    if (train_id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入要查询的列车号"));
        return;
    }
    //qDebug() << train_id;
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "query_train " + train_id + "\n";

    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    QString ret = QString(backend.readAllStandardOutput());
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    //qDebug() << "ret : " << ret;
    if(ret == "0\r\n") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("查找不到该列车"));
        return;
    }

    int pricenum = ret.section(' ', 4, 4).toInt();
    //qDebug() << "pricenum : " << pricenum;
    ui->tableWidget->setColumnCount(pricenum + 4);
    QStringList header;
    header << trUtf8("车站") << trUtf8("到站时间") << trUtf8("离站时间") << trUtf8("停留时间");
    for(int i = 0 ; i < pricenum ; ++ i) {
        header << ret.section('\r', 0, 0).section(' ', 5 + i, 5 + i);
    }
    //qDebug() << header;
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int stationnum = ret.section(' ', 3, 3).toInt();
    for (int i = 0; i < stationnum; i++) {
        QString ss = ret.section('\r', 1 + i, 1 + i).section('\n', 1, 1);
        ui->tableWidget->insertRow(i);
        for (int j = 0; ss != ""; j++) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(ss.section(' ', 0, 0)));
            ss = ss.section(' ', 1);
            //qDebug() << ss;
        }
    }
}
