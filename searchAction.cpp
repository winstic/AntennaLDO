#include "searchAction.h"
searchAction::searchAction(QWidget *parent)
	: QWidgetAction(parent)
{
    QPushButton *searchButton = new QPushButton("Search");
	searchEdit = new QLineEdit();
	searchEdit->setPlaceholderText("搜索天线模型");
	searchEdit->setClearButtonEnabled(true);
    QWidget *searchWidget = new QWidget(NULL);
	searchWidget->setWindowFlags(Qt::FramelessWindowHint);
	QHBoxLayout *lay = new QHBoxLayout();
	lay->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
	lay->addWidget(searchEdit);
	lay->addWidget(searchButton);
	lay->setStretch(0, 20);
	lay->setStretch(1, 5);
	lay->setStretch(2, 1);
	searchWidget->setLayout(lay);
	this->setDefaultWidget(searchWidget);

    connect(searchButton, SIGNAL(clicked()), parent, SLOT(slot_clickSearchButton()));
    connect(searchEdit, SIGNAL(textChanged(QString)), parent, SLOT(slot_searchTextChange(QString)));
}

/*QWidget * searchAction::createWidget(QWidget *parent)
{
	searchWidget->setParent(parent);
	return searchWidget;
}*/

QString searchAction::getEditValue() const{
    return searchEdit->text();
}
