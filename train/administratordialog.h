#ifndef ADMINISTRATORDIALOG_H
#define ADMINISTRATORDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class administratorDialog;
}

class administratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit administratorDialog(QWidget *parent = 0, int _id = 0);
    ~administratorDialog();

private slots:
    void on_logoutButton_clicked();

    void on_cleanButton_clicked();

    void on_modifyProfileButton_clicked();

    void on_modifyPrivilegeButton_clicked();

    void on_buyTicketButton_clicked();

    void on_refundTicketButton_clicked();

    void on_saleTrainButton_clicked();

    void on_deleteTrainButton_clicked();

    void on_addTrainButton_clicked();

    void on_modifyTrainButton_clicked();

    void on_queryTrainButton_clicked();

    void on_queryTransferButton_clicked();

    void on_queryOrderButton_clicked();

    void on_queryTicketButton_clicked();

private:
    Ui::administratorDialog *ui;
    int id;
    void closeEvent(QCloseEvent *event);
};

#endif // ADMINISTRATORDIALOG_H
