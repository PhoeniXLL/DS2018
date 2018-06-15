#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = 0);
    ~registerDialog();

private slots:
    void on_registerButton_clicked();

private:
    Ui::registerDialog *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // REGISTERDIALOG_H
