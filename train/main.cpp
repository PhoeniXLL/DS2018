#include "initialdialog.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap("ad.png"));
    splash.setDisabled(true);
    splash.show();
    QDateTime start = QDateTime::currentDateTime();
    QDateTime now;
    do {
        now = QDateTime::currentDateTime();
    } while (start.secsTo(now) <= 2);
    initialDialog w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
