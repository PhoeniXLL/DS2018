#ifndef DELETETRAINDIALOG_H
#define DELETETRAINDIALOG_H

#include <QDialog>

namespace Ui {
class deleteTrainDialog;
}

class deleteTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deleteTrainDialog(QWidget *parent = 0);
    ~deleteTrainDialog();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::deleteTrainDialog *ui;
};

#endif // DELETETRAINDIALOG_H
