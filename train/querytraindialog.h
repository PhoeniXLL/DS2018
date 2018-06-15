#ifndef QUERYTRAINDIALOG_H
#define QUERYTRAINDIALOG_H

#include <QDialog>

namespace Ui {
class queryTrainDialog;
}

class queryTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit queryTrainDialog(QWidget *parent = 0);
    ~queryTrainDialog();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::queryTrainDialog *ui;
};

#endif // QUERYTRAINDIALOG_H
