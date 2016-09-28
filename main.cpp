#include "mainwindow.h"
#include <QApplication>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    MainWindow w;
    w.showMaximized();
    //w.showMaximized();
    //w.show();

    return a.exec();
}
