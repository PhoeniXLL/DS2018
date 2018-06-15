#ifndef QUERYTRANSFERDIALOG_H
#define QUERYTRANSFERDIALOG_H

#include <QDialog>

namespace Ui {
class queryTransferDialog;
}

class queryTransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit queryTransferDialog(QWidget *parent = 0);
    ~queryTransferDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::queryTransferDialog *ui;
};

#endif // QUERYTRANSFERDIALOG_H
