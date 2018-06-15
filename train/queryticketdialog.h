#ifndef QUERYTICKETDIALOG_H
#define QUERYTICKETDIALOG_H

#include <QDialog>

namespace Ui {
class queryTicketDialog;
}

class queryTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit queryTicketDialog(QWidget *parent = 0, int _id = 0);
    ~queryTicketDialog();

private slots:
    void on_searchButton_clicked();
    void onCellDoubleClicked(int row, int column);

private:
    Ui::queryTicketDialog *ui;
    int id;
    QString loc1;
    QString loc2;
    QString date;
    QString catalog;
};

#endif // QUERYTICKETDIALOG_H
