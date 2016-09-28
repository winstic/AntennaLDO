#ifndef SEARCHACTION_H
#define SEARCHACTION_H

#include <QWidgetAction>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QWidget>
#include <QSpacerItem>

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
