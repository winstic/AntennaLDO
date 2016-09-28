#include <QtWidgets>

#include "mdichild.h"

MdiChild::MdiChild(QWidget *parent) : QWidget(parent), isClose(false){
    setAttribute(Qt::WA_DeleteOnClose);
    myScroll = new QScrollBar(Qt::Vertical);
}

bool MdiChild::loadFile(const QString &fileName){
    //QFile file(fileName);
    //if(!file.open(QFile::ReadOnly | QFile::))
    return true;
}

QScrollBar* MdiChild::getAtnScroll(){
    return myScroll;
}

/*void MdiChild::resizeEvent(QResizeEvent *event){
    int width = this->width() - myScroll->width();
    int columns = width / (MBNTICON_WH + MBNTDIS);
    columns = columns == 0 ? 1 : columns;
    int rows = NUMOFANTENNA / columns;
    rows = NUMOFANTENNA % columns == 0 ? rows : (rows+1);
    if(height() >= rows*(MBNTICON_HT+MBNTDIS)){
        myScroll->setMinimum(0);
        myScroll->setMaximum(0);
        myScroll->setHidden(true);
    }
    else{
        myScroll->setHidden(false);
        int itemHeight = MBNTICON_HT + MBNTDIS;
        myScroll->setMinimum(0);
        int maxH = rows * itemHeight - height();
        int pageStep = height() - maxH;
        myScroll->setMaximum(maxH);
        myScroll->setPageStep(pageStep);
        myScroll->setSingleStep(10);
    }
   //int listViewHeight = rows * (MBNTICON_HT + MBNTDIS);
   //listViewHeight = listViewHeight > this->height() ? listViewHeight : this->height();
   //myListViewBTN->resize(this->size().width(),listViewHeight);
   //emit SendResizeSignal(rows, columns);
   QWidget::resizeEvent(event);
}*/

void MdiChild::closeEvent(QCloseEvent *event){
    isClose = true;
    emit signal_sendClose(isClose);
    QWidget::closeEvent(event);
}
