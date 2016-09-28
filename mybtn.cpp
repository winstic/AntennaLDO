#include <QtWidgets>
#include <QPen>
#include "mybtn.h"

myBtn::myBtn(const QString &strImage, const QString &strText, QWidget *parent): QToolButton(parent),
bOver(false), bPress(false), bDoubleClick(false), bImage(strImage), bText(strText){
    //text color
    QPalette textPalette = palette();
    textPalette.setColor(QPalette::ButtonText, QColor(0,0,0));
    setPalette(textPalette);
    //strong text
    //QFont &textFont = const_cast<QFont &>(font());
    //textFont.setWeight(QFont::Bold);
    //style
    setStyleSheet("QToolButton{border:0px;}");
    //size
    setIconSize(QSize(MBNTICON_WH, MBNTICON_HT));
    resize(MBNTICON_WH, MBNTICON_WH);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //image and text
    setIcon(QPixmap(strImage));
    setText(strText);

    //connect(this, SIGNAL(pressed()), this, SLOT(slot_slotbPress()));
    //connect(this, SIGNAL())
}

// 鼠标移到按钮上时
void myBtn::enterEvent(QEvent *event){
    setOver(true);
}

// 鼠标离开时
void myBtn::leaveEvent(QEvent *event){
    setOver(false);
}

void myBtn::setOver(bool bEnable){
    if(bEnable != bOver){
        //设置bOver标志位
        bOver = bEnable;
        update();
    }
}

void myBtn::setPress(bool bEnable){
    if(bEnable != bPress){
        //设置bPress标志位
        bPress = bEnable;
        update();
    }
}

void myBtn::slot_slotbPress(){
    setPress(true);
}

void myBtn::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(bPress){
        //绘制被按下时的效果
        painterInfo(150, 200, &painter);
    }
    else if(bOver){
        // 按钮没有被按下且鼠标移动到按钮上
        painterInfo(50, 100, &painter);
    }
    //调用基类的重绘事件以显示图像文本
    QToolButton::paintEvent(event);
}

void myBtn::painterInfo(int nTopPartOpacity, int nBottomPartOpacity, QPainter *pPainter){
    //设置画笔
    QPen objPen(Qt::NoBrush, 1);
    pPainter->setPen(objPen);
    //设置渐变画刷
    QLinearGradient objLinear(rect().topLeft(), rect().bottomLeft());
    //顶部颜色和透明度
    objLinear.setColorAt(0, QColor(240, 240, 240, nTopPartOpacity));
    //中间颜色和透明度
    objLinear.setColorAt(0.5, QColor(240, 240, 240, 240));
    //底部颜色和透明度
    objLinear.setColorAt(1, QColor(240, 240, 240, nBottomPartOpacity));

    QBrush objBrush(objLinear);
    pPainter->setBrush(objBrush);
    //画圆角矩形
    pPainter->drawRoundedRect(rect(), 5, 5);
}

void myBtn::mouseDoubleClickEvent(QMouseEvent *event){
    bool isDoubleClick = true;
    emit signal_sendDoubleClickBtn(isDoubleClick);
}

void myBtn::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton)
        QMessageBox::information(this, "infomation", "Test Right Click");
}
