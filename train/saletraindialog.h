#ifndef SALETRAINDIALOG_H
#define SALETRAINDIALOG_H

#include <QDialog>

namespace Ui {
class saleTrainDialog;
}

class saleTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saleTrainDialog(QWidget *parent = 0);
    ~saleTrainDialog();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::saleTrainDialog *ui;
};

#endif // SALETRAINDIALOG_H
