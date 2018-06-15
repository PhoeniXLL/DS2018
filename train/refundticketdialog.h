#ifndef REFUNDTICKETDIALOG_H
#define REFUNDTICKETDIALOG_H

#include <QDialog>

namespace Ui {
class refundTicketDialog;
}

class refundTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit refundTicketDialog(QWidget *parent = 0, int _id = 0, QString data = "");
    ~refundTicketDialog();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::refundTicketDialog *ui;
    int id;
};

#endif // REFUNDTICKETDIALOG_H
