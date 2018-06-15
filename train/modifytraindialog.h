#ifndef MODIFYTRAINDIALOG_H
#define MODIFYTRAINDIALOG_H

#include <QDialog>

namespace Ui {
class modifyTrainDialog;
}

class modifyTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit modifyTrainDialog(QWidget *parent = 0);
    ~modifyTrainDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::modifyTrainDialog *ui;
};

#endif // MODIFYTRAINDIALOG_H
