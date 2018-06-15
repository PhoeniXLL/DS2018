#ifndef QUERYORDERDIALOG_H
#define QUERYORDERDIALOG_H

#include <QDialog>

namespace Ui {
class queryOrderDialog;
}

class queryOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit queryOrderDialog(QWidget *parent = 0, int _id = 0);
    ~queryOrderDialog();

private slots:
    void on_searchButton_clicked();
    void onCellDoubleClicked(int row, int column);

private:
    Ui::queryOrderDialog *ui;
    int id;
    QString buyerId;
    QString date;
    QString catalog;
};

#endif // QUERYORDERDIALOG_H
