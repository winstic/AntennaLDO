#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>
#include "global.h"

class MdiChild : public QWidget{
    Q_OBJECT
public :
    MdiChild(QWidget *parent = 0);
    bool loadFile(const QString &fileName);
    ~MdiChild(){}
    QScrollBar* getAtnScroll();

private:
    QString filePath;
    QScrollBar* myScroll;
    bool isClose;

signals:
    void signal_sendClose(bool);

protected:
    //void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent* event);

private slots:
    //void SendResizeSignal(int, int);

};

#endif // MDICHILD_H
