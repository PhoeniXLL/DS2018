#ifndef INITIALDIALOG_H
#define INITIALDIALOG_H

#include <QDialog>

namespace Ui {
class initialDialog;
}

class initialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit initialDialog(QWidget *parent = 0);
    ~initialDialog();

private slots:
    void on_registerButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::initialDialog *ui;
};

#endif // INITIALDIALOG_H
