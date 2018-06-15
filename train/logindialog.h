#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

private slots:
    void on_loginButton_clicked();
    void onTimeOut();

private:
    Ui::loginDialog *ui;
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    QString captcha;
    Qt::GlobalColor *colors;
    QTimer timer;
    Qt::GlobalColor *getColors();
    QString getCaptcha();
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // LOGINDIALOG_H
