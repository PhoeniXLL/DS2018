#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = 0, int _id = 0);
    ~userDialog();

private slots:
    void on_logoutButton_clicked();

    void on_modifyProfileButton_clicked();

    void on_buyTicketButton_clicked();

    void on_refundTicketButton_clicked();

    void on_queryTransferButton_clicked();

    void on_queryTrainButton_clicked();

    void on_queryTicketButton_clicked();

    void on_queryOrderButton_clicked();

private:
    Ui::userDialog *ui;
    int id;
    void closeEvent(QCloseEvent *event);
};

#endif // USERDIALOG_H
