#include "mainwindow.h"
#include <QApplication>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    //open sqlite3 connect
    new sqliteManage();
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
