#ifndef STATIONDIALOG_H
#define STATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDoubleSpinBox>
class addtrainDialog;

namespace Ui {
class stationDialog;
}

class stationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stationDialog(QWidget *parent = 0);

    ~stationDialog();

    addtrainDialog *father;

    void setType(int kind);

    void getReadyStation(QStringList list);

    void getReadyPrice(QStringList list);

private slots:
    void on_arriveBox_stateChanged(int arg1);

    void on_startBox_stateChanged(int arg1);

    void on_okButton_clicked();

private:
    Ui::stationDialog *ui;
    QLabel *pricelabel[6];
    QDoubleSpinBox *pricebox[6];
    int type, pricenum;
};

#endif // STATIONDIALOG_H
