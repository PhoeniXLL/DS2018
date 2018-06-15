#ifndef BUYTICKETDIALOG_H
#define BUYTICKETDIALOG_H

#include <QDialog>

namespace Ui {
class buyTicketDialog;
}

class buyTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit buyTicketDialog(QWidget *parent = 0, int _id = 0, QString data = "");
    ~buyTicketDialog();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::buyTicketDialog *ui;
    int id;
};

#endif // BUYTICKETDIALOG_H
