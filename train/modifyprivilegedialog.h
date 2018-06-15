#ifndef MODIFYPRIVILEGEDIALOG_H
#define MODIFYPRIVILEGEDIALOG_H

#include <QDialog>

namespace Ui {
class modifyPrivilegeDialog;
}

class modifyPrivilegeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit modifyPrivilegeDialog(QWidget *parent = 0, int _id = 0);
    ~modifyPrivilegeDialog();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::modifyPrivilegeDialog *ui;
    int id;
};

#endif // MODIFYPRIVILEGEDIALOG_H
