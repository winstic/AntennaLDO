#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QMenu>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "macrodefined.h"
#include "designWizard.h"
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
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName, const QString &atnName);

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

    //cursor position index
    QModelIndex currentIndex;
};

#endif // TREEMODEL_H
