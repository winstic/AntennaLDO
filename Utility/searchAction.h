#ifndef SEARCHACTION_H
#define SEARCHACTION_H

#include <QtWidgets>

class  searchAction :public QWidgetAction
{
public:
	searchAction(QWidget *parent = 0);
    ~searchAction(){}

    //QWidget * createWidget(QWidget *parent);
    QString getEditValue() const;

private:
	QLineEdit *searchEdit;

private slots:
	
};

#endif
