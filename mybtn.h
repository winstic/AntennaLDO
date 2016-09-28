#ifndef MYBTN_H
#define MYBTN_H

#include "global.h"

class myBtn : public QToolButton{
    Q_OBJECT
public :
    myBtn(const QString &strImage, const QString &strText, QWidget *parent = 0);
    ~myBtn(){}
    void setOver(bool bEnable);
    void setPress(bool bEnable);
    //绘制背景渐变
    void painterInfo(int nTopPartOpacity, int nBottomPartOpacity, QPainter *pPainter);

private:
    bool bOver;           //鼠标移动到按钮上
    bool bPress;          //点击按钮
    bool bDoubleClick;    //双击按钮
    const QString bImage;
    const QString bText;

signals:
    void signal_sendDoubleClickBtn(bool);

protected:
    // 重载函数
    void enterEvent(QEvent *event);                 //鼠标移到按钮上
    void leaveEvent(QEvent *event);                 //鼠标离开按钮
    void paintEvent(QPaintEvent *event);            //重绘事件
    void mouseDoubleClickEvent(QMouseEvent *event); //鼠标双击事件
    void mousePressEvent(QMouseEvent *event);       //鼠标点击事件

private slots:
    void slot_slotbPress();

};

#endif // MYBTN_H
