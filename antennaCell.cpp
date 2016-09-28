#include "antennaCell.h"
antennaCell::antennaCell(QString path, QString name, QWidget* parent):QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();
    atnName = new QLabel(name);
    atnPhoto = new QLabel;
    atnPhoto->setPixmap(QPixmap(path));
	//hLayout->addWidget((QWidget *)m_icon);
    vLayout->addWidget(atnPhoto);
    vLayout->addWidget(atnName);
	vLayout->setStretch(0,2);
	vLayout->setStretch(1,1);
    hLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
	hLayout->addLayout(vLayout);
    hLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(hLayout);

	setMouseTracking(true);
}

QString antennaCell::getAtnName() const{
    return atnName->text();
}

QLabel* antennaCell::getAtnPhoto() const{
    return atnPhoto;
}

//void antennaCell::enterEvent(QEvent *e)
//{
//	
//}

/*void antennaCell::mouseMoveEvent(QMouseEvent* event)
{

	int index = m_sqliteManage->m_antennaName_list.indexOf(m_name->text());
	QString info = m_sqliteManage->m_antennaInfo_list[index];
	if (info.size() >= 30)
	{
		info=info.mid(0, 30);
		info += "...";
	}
	QToolTip::showText(cursor().pos(), info, 0);
	//setToolTip(info);
}*/
