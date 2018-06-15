#ifndef MODIFYPROFILEDIALOG_H
#define MODIFYPROFILEDIALOG_H

#include <QDialog>

namespace Ui {
class modifyProfileDialog;
}

class modifyProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit modifyProfileDialog(QWidget *parent = 0, int _id = 0);
    ~modifyProfileDialog();

private slots:
    void on_applyButton_clicked();

private:
    Ui::modifyProfileDialog *ui;
    int id;
};

#endif // MODIFYPROFILEDIALOG_H
