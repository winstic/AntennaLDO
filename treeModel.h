﻿#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QMenu>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "macrodefined.h"
#include "designWizard.h"
#include "designtab.h"
#include "parsejson.h"
#include "global.h"
#include "run.h"
//#include "config.h"

class treeModel : public QTreeView{

    Q_OBJECT

public:
    treeModel(QTreeView* m_tree);
    ~treeModel(){}

    QList<QStandardItem*> getRoots();           //获取所有节点
    QStandardItem* getProNode();                //获取项目工程节点
    QList<QStandardItem*> getFolderNode();      //获取文件夹节点

    void initMenu();
    void initIcon();
    //void showTree();
    bool parseXML(const QString &fileName);
    bool writeXMLFile(const QString &fileName, const QString &atnName);
    bool updateXMLFile(const QString &fileName, const QStandardItem *item, const QStandardItem *child);

    inline QMenu* getProjectMenu() {return mProjectMenu;}
    inline QMenu* getAtnDesignMenu() {return mAtnDesignMenu;}
    inline QMenu* getAtnOptimizationMenu() {return mAtnOptimizationMenu;}
    inline QMenu* getItemMenu() {return mItemMenu;}
    inline QMenu* getItemViewMenu() {return mItemViewMenu;}
    inline QMenu* getResultMenu() {return mResultMenu;}

private slots:
    void slot_showAll();
    void slot_hideAll();
    void slot_add();
    void slot_run();
    void slot_del();
    void slot_openFile();
    void slot_showResult();

    //mouse right click
    void slot_customContextMenuRequested(const QPoint &pos);

private:
    void parseProjectElement(const QDomElement &element);
    void parseNodeElement(const QDomElement &element, QStandardItem *parent);
    void parseItemElement(const QDomElement &element, QStandardItem *parent);

    QMap<QString, QIcon> IconMap;
    QTreeView *mTree;
    QStandardItemModel* tModel;
    QStandardItem *treeRoot;
    //different menu can respond different right click
    QMenu* mProjectMenu;    
    QMenu* mAtnDesignMenu;
    QMenu* mAtnOptimizationMenu;
    QMenu* mResultMenu;
    QMenu* mItemMenu;
    QMenu* mItemViewMenu;

    //!Actions
    QAction* actClose;
    QAction* actDel;
    QAction* actHideAll;
    QAction* actShowAll;
    QAction* actAdd;
    QAction* actRun;
    QAction* actOpenFile;
    QAction* actShowResult;
    //!

    //cursor position index
    QModelIndex currentIndex;
};

#endif // TREEMODEL_H
