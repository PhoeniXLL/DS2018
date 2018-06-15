#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QProcess>
#include "userdialog.h"
#include "administratordialog.h"
#include "initialdialog.h"
#include <QPainter>
#include <QTime>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    colors = getColors();
    captcha = getCaptcha();
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer.start(500);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_loginButton_clicked()
{
    QString id = ui->lineEdit_1->text();
    if (id == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入你的用户id"));
        return;
    }
    QString password = ui->lineEdit_2->text();
    if (password == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入你的密码"));
        return;
    }
    QString captcha = ui->lineEdit_3->text();
    if (captcha == "") {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("请输入验证码"));
        return;
    }
    if (captcha.toLower() != this->captcha.toLower()) {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("验证码错误"));
        this->captcha = getCaptcha();
        repaint();
        return;
    }
    QProcess backend;
    backend.start("backend.exe");
    backend.waitForStarted();
    QString command = "login " + id + " " + password + "\n";
    backend.write(command.toStdString().c_str());
    backend.waitForReadyRead();
    int ret = QString(backend.readAllStandardOutput()).toInt();
    backend.write("exit\n");
    backend.waitForFinished();
    backend.close();
    if (ret) {
        QMessageBox::information(this, trUtf8("成功"), trUtf8("登陆成功"));
        QProcess backend;
        backend.start("backend.exe");
        backend.waitForStarted();
        QString command = "query_profile " + id + "\n";
        backend.write(command.toStdString().c_str());
        backend.waitForReadyRead();
        QString ret = QString(backend.readAllStandardOutput());
        backend.write("exit\n");
        backend.waitForFinished();
        backend.close();
        int privilege = ret.section(' ', 3, 3).toInt();
        if (privilege == 1) {
            userDialog *userdialog = new userDialog(0, id.toInt());
            hide();
            userdialog->show();
        } else {
            administratorDialog *administratordialog = new administratorDialog(0, id.toInt());
            hide();
            administratordialog->show();
        }
    } else {
        QMessageBox::critical(this, trUtf8("错误"), trUtf8("密码不正确，请检查你的用户id或密码"));
        ui->lineEdit_1->clear();
        ui->lineEdit_2->clear();
    }
}

void loginDialog::onTimeOut()
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    colors = getColors();
    update();
}

void loginDialog::closeEvent(QCloseEvent *event)
{
    initialDialog *initialdialog = new initialDialog();
    initialdialog->show();
}

void loginDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(201, 200, 120, 31, Qt::white);
    painter.setFont(QFont("Comic Sans MS", 12));
    for (int i = 0; i < 4; i++) {
        painter.setPen(colors[i]);
        painter.drawText(201 + 30 * i, 200, 30, 31, Qt::AlignCenter, QString(captcha[i]));
    }
    for (int i = 0; i < 150; i++) {
        painter.setPen(colors[i % 4]);
        painter.drawPoint(201 + qrand() % 120, 200 + qrand() % 31);
    }
}

Qt::GlobalColor *loginDialog::getColors()
{
    static Qt::GlobalColor colors[4];
    for (int i = 0; i < 4; i++) {
        colors[i] = static_cast<Qt::GlobalColor>(2 + qrand() % 16);
    }
    return colors;
}

QString loginDialog::getCaptcha()
{
    QString ret = "";
    for (int i = 0; i < 4; i++) {
        int c = qrand() % 2 ? 'a' : 'A';
        ret += static_cast<QChar>(c + qrand() % 26);
    }
    return ret;
}

void loginDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (QRect(201, 200, 120, 31).contains(event->pos())) {
        captcha = getCaptcha();
        repaint();
    }
}
