#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QMenu>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "macrodefined.h"
#include "designWizard.h"
#include "optimizeWizard.h"
#include "designtab.h"
#include "optimizetab.h"
#include "modelfile.h"
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
    inline QMenu* getAtnOptimizeMenu() {return mAtnOptimizeMenu;}
    inline QMenu* getResultMenu() {return mResultMenu;}
    inline QMenu* getItemViewMenu() {return mItemViewMenu;}
    inline QMenu* getItemDesignMenu() {return mItemDesignMenu;}
    inline QMenu* getItemOptimizeMenu() {return mItemOptimizeMenu;}

private slots:
    void slot_showAll();
    void slot_hideAll();
    void slot_addDesign();
    void slot_addOptimize();
    void slot_run();
    void slot_interrupt();
    void slot_stop();
    void slot_del();
    void slot_openFile();
    void slot_modifyDesignVar();
    void slot_modifyOptimizeVar();
    void slot_showResult();

    //mouse right click
    void slot_customContextMenuRequested(const QPoint &pos);
    void slot_doubleClick(QModelIndex itemIndex);

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
    QMenu* mAtnOptimizeMenu;
    QMenu* mResultMenu;
    QMenu* mItemDesignMenu;
    QMenu* mItemOptimizeMenu;
    QMenu* mItemViewMenu;

    //!Actions
    QAction* actClose;
    QAction* actDel;
    QAction* actHideAll;
    QAction* actShowAll;
    QAction* actAddDesign;
    QAction* actAddOptimize;
    QAction* actRun;
    QAction* actInterrupt;
    QAction* actStop;
    QAction* actOpenFile;
    QAction* actModifyDesignVar;
    QAction* actModifyOptimizeVar;
    QAction* actShowResult;
    //!

    //cursor position index
    QModelIndex currentIndex;
};

#endif // TREEMODEL_H
