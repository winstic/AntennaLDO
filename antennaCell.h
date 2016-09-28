#ifndef ANTENNACELL_H
#define ANTENNACELL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QToolTip>
#include "sqliteManage.h"
class antennaCell :public QWidget
{
public:
    antennaCell(QString path, QString name, QWidget* parent = 0);
	/*void enterEvent(QEvent *);*/
    //void mouseMoveEvent(QMouseEvent* event);
	//QPushButton *m_detail_btn;

    QString getAtnName() const;
    QLabel* getAtnPhoto() const;
private slots:

private:
    QLabel *atnPhoto;
    QLabel *atnName;

};

#endif
