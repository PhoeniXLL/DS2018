#include "addtraindialog.h"
#include "ui_addtraindialog.h"
#include <QProcess>
#include <QMessageBox>

addtrainDialog::addtrainDialog(QWidget *parent, QString _train_id) :
    QDialog(parent),
    ui(new Ui::addtrainDialog),
    train_id(_train_id)
{
    ui->setupUi(this);

    ui->priceWidget->setShowGrid(false);
    //ui->priceWidget->verticalHeader()->setVisible(false);
    ui->priceWidget->setColumnCount(1);

   //设置表格
    ui->priceWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  //ui->priceWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->priceWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList header;
    header << trUtf8("票价种类");   //表头
    ui->priceWidget->setHorizontalHeaderLabels(header);

    ui->priceWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->priceWidget->setAlternatingRowColors(true);

/**************************************************************************/

    ui->stationWidget->setShowGrid(false);
    //ui->stationWidget->verticalHeader()->setVisible(false);
    ui->stationWidget->setColumnCount(4);

    //设置表格
    ui->stationWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  //ui->stationWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->stationWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList stationheader;
    stationheader << trUtf8("车站") << trUtf8("到站时间") << trUtf8("离站时间") << trUtf8("停留时间");   //表头
    ui->stationWidget->setHorizontalHeaderLabels(stationheader);

    ui->stationWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->stationWidget->setAlternatingRowColors(true);

    if (train_id != "") {
        ui->trainIdLineEdit->setText(train_id);
        ui->trainIdLineEdit->setFocusPolicy(Qt::NoFocus);
    }
}

addtrainDialog::~addtrainDialog()
{
    delete ui;
}

void addtrainDialog::addprice(QString name)
{
    int row = ui->priceWidget->rowCount();
    ui->priceWidget->insertRow(row);
    ui->priceWidget->setItem(row, 0, new QTableWidgetItem(name));
    ui->stationWidget->insertColumn(row + 4);
    //qDebug() << "oh_no";
    ui->stationWidget->setHorizontalHeaderItem(row + 4, new QTableWidgetItem(name));
    for(int i = 0 ; i < ui->stationWidget->rowCount() ; ++ i) {
        ui->stationWidget->setItem(i, row + 4, new QTableWidgetItem("0.00"));
    }
    //qDebug() << "oh_Yes";
}

void addtrainDialog::modifyprice(QString name)
{
    int row = ui->priceWidget->currentRow();
    ui->priceWidget->item(row, 0)->setText(name);
    ui->stationWidget->horizontalHeaderItem(row + 4)->setText(name);
}

void addtrainDialog::addStation(QStringList list)
{
    int row = ui->stationWidget->rowCount();
    ui->stationWidget->insertRow(row);
    for(int i = 0 ; i < ui->stationWidget->columnCount() ; ++ i) {
        ui->stationWidget->setItem(row, i, new QTableWidgetItem(list.at(i)));
    }
}

void addtrainDialog::modifyStation(QStringList list)
{
    int row = ui->stationWidget->currentRow();
    for(int i = 0 ; i < ui->stationWidget->columnCount() ; ++ i) {
        ui->stationWidget->setItem(row, i, new QTableWidgetItem(list.at(i)));
    }
}

void addtrainDialog::on_addButton_1_clicked()
{
    now_price = new priceDialog;
    now_price->father = this;
    now_price->setType(0);
    now_price->exec();
}

void addtrainDialog::on_delButton_1_clicked()
{
    if(ui->priceWidget->rowCount() == 0) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前已无票价名称"));
        return;
    }
    QTableWidgetItem *now_item = ui->priceWidget->currentItem();
    if(ui->priceWidget->isItemSelected(now_item)) {
        int row = now_item->row();
        ui->priceWidget->removeRow(row);
        ui->stationWidget->removeColumn(row + 4);
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前票价名称未选中"));
        return;
    }
}

void addtrainDialog::on_modifyButton_1_clicked()
{
    if(ui->priceWidget->rowCount() == 0) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前已无票价名称"));
        return;
    }
    QTableWidgetItem *now_item = ui->priceWidget->currentItem();
    if(ui->priceWidget->isItemSelected(now_item)) {
        int row = now_item->row();
        now_price = new priceDialog();
        now_price->setType(1);
        now_price->father = this;
        now_price->getReadyPrice(ui->priceWidget->item(row, 0)->text());
        now_price->exec();
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前票价名称未选中"));
        return;
    }

}

void addtrainDialog::on_addButton_2_clicked()
{
    now_station = new stationDialog();
    now_station->father = this;
    QStringList list;
    for(int i = 4 ; i < ui->stationWidget->columnCount() ; ++ i) {
        list << ui->stationWidget->horizontalHeaderItem(i)->text();
    }
    now_station->getReadyPrice(list);
    now_station->setType(0);
    now_station->exec();
}

void addtrainDialog::on_delButton_2_clicked()
{
    if(ui->stationWidget->rowCount() == 0) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前已无车站"));
        return;
    }
    QTableWidgetItem *now_item = ui->stationWidget->currentItem();
    if(ui->stationWidget->isItemSelected(now_item)) {
        ui->stationWidget->removeRow(now_item->row());
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前车站未选中"));
        return;
    }
}

void addtrainDialog::on_modifyButton_2_clicked()
{
    if(ui->stationWidget->rowCount() == 0) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前已无车站"));
        return;
    }
    QTableWidgetItem *now_item = ui->stationWidget->currentItem();
    if(ui->stationWidget->isItemSelected(now_item)) {
        int row = now_item->row();
        now_station = new stationDialog();
        now_station->setType(1);
        now_station->father = this;
        QStringList list1;
        for(int i = 4 ; i < ui->stationWidget->columnCount() ; ++ i) {
            list1 << ui->stationWidget->horizontalHeaderItem(i)->text();
        }
        now_station->getReadyPrice(list1);

        QStringList list2;
        for(int i = 0 ; i < ui->stationWidget->columnCount() ; ++ i) list2 << ui->stationWidget->item(row, i)->text();
        now_station->getReadyStation(list2);
        now_station->exec();
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("当前车站未选中"));
        return;
    }
}

void addtrainDialog::on_comfirmButton_clicked()
{
    if (ui->trainIdLineEdit->text() == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车号不应为空"));
        return;
    }
    if (ui->nameLineEdit->text() == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车名称不应为空"));
        return;
    }
    if (ui->catalogLineEdit->text() == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车类别不应为空"));
        return;
    }
    if (ui->priceWidget->rowCount() == 0) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("票价种类不应为空"));
        return;
    }
    if (ui->stationWidget->rowCount() <= 1) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("列车应至少有两站"));
        return;
    }
    if (ui->stationWidget->item(0, 2)->text() == "xx:xx") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("始发站应有离站时间"));
        return;
    }
    for (int i = 1; i < ui->stationWidget->rowCount() - 1; i++) {
        if (ui->stationWidget->item(i, 1)->text() == "xx:xx") {
            QMessageBox::critical(this, trUtf8("错误"), trUtf8("中间站%1应有到站时间").arg(ui->stationWidget->item(i, 0)->text()));
            return;
        }
        if (ui->stationWidget->item(i, 2)->text() == "xx:xx") {
            QMessageBox::critical(this, trUtf8("错误"), trUtf8("中间站%1应有离站时间").arg(ui->stationWidget->item(i, 0)->text()));
            return;
        }
    }
    if (ui->stationWidget->item(ui->stationWidget->rowCount() - 1, 1)->text() == "xx:xx") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("终点站应有到站时间"));
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    //qDebug() << ui->catalogLineEdit->text();
    QString command = "add_train " + ui->trainIdLineEdit->text() + " " + ui->nameLineEdit->text() + " " + ui->catalogLineEdit->text() + " "
                      + QString::number(ui->stationWidget->rowCount()) + " " + QString::number(ui->priceWidget->rowCount());
    for (int i = 0; i < ui->priceWidget->rowCount(); i++) {
        command += " " + ui->priceWidget->item(i, 0)->text();
    }
    command += "\n";
    //qDebug() << command;
    backend.write(command.toStdString().c_str());
    for (int i = 0; i < ui->stationWidget->rowCount(); i++) {
        command = "";
        for (int j = 0; j < ui->stationWidget->columnCount(); j++) {
            command += (j >= 4 ? "￥" : "") + ui->stationWidget->item(i, j)->text() + (j == ui->stationWidget->columnCount() - 1 ? "" : " ");
        }
        command += "\n";
        //qDebug() << command;
        backend.write(command.toStdString().c_str());
    }
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        QMessageBox::information(this, trUtf8("成功"), trUtf8("添加车次成功"));
        close();
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("添加车次失败"));
        ui->trainIdLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->catalogLineEdit->clear();
        ui->priceWidget->clear();
        ui->priceWidget->setRowCount(0);
        ui->stationWidget->clear();
        ui->stationWidget->setRowCount(0);
    }
}
