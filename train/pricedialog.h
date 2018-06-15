#ifndef PRICEDIALOG_H
#define PRICEDIALOG_H

#include <QDialog>

class addtrainDialog;

namespace Ui {
class priceDialog;
}

class priceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit priceDialog(QWidget *parent = 0);
    ~priceDialog();
    addtrainDialog *father;
    void getReadyPrice(QString);
    void setType(int kind);

private slots:
    void on_pushButton_clicked();

private:
    int type;
    Ui::priceDialog *ui;
};

#endif // PRICEDIALOG_H
