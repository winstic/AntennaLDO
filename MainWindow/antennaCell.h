#ifndef ANTENNACELL_H
#define ANTENNACELL_H

#include <QtWidgets>
#include "../Global/macrodefined.h"
#include "../Utility/sqliteManage.h"
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
    QLabel *atnNameLabel;
    QString atnName;

};

#endif
