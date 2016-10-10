#include "treeModel.h"
#include <QDebug>

treeModel::treeModel(QTreeView* m_tree){
    //QStandardItemModel* tModel = new QStandardItemModel(mTree);
    mTree = m_tree;
    mProjectMenu = new QMenu;
    mAtnDesignMenu = new QMenu;
    mAtnOptimizationMenu = new QMenu;
    mItemMenu = new QMenu;
    mItemViewMenu = new QMenu;
    mResultMenu = new QMenu;
    //actRightClick = nullptr;
    initMenu();
    initIcon();
    connect(mTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slot_customContextMenuRequested(const QPoint&)));
}

void treeModel::initIcon(){
    IconMap[QStringLiteral("treeNode")] = QIcon(QStringLiteral("./images/node.png"));
    IconMap[QStringLiteral("treeItem")] = QIcon(QStringLiteral("./images/item.png"));
}

bool treeModel::readFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, tr("Error"), tr("Cannot read file %1").arg(fileName));
        return false;
    }
    QDomDocument doc;
    QString error;
    int row, column;
    if(!doc.setContent(&file, false, &error, &row, &column)){
        QMessageBox::critical(this, tr("Error"), tr("Parse error at row %1, column %2: %3")
                              .arg(row).arg(column).arg(error));
        return false;
    }
    file.close();
    QDomElement xmlRoot = doc.documentElement();
    if("project" != xmlRoot.tagName()){
        QMessageBox::critical(this, tr("Error"), tr("Not a project file"));
        return false;
    }

    tModel = new QStandardItemModel(mTree);
    QStringList header;    
    header << xmlRoot.attribute("name");
    tModel->setHorizontalHeaderLabels(header);

    QString projectName = QFileInfo(fileName).fileName().split(".").at(0);
    treeRoot = new QStandardItem(IconMap[QStringLiteral("treeNode")], projectName);
    treeRoot->setData(MARK_PROJECT, ROLE_MARK);
    tModel->appendRow(treeRoot);
    parseProjectElement(xmlRoot);

    mTree->setModel(tModel);
    mTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mTree->setContextMenuPolicy(Qt::CustomContextMenu);        //设置右键菜单
    mTree->expandAll();
    return true;
}

bool treeModel::writeFile(const QString &fileName, const QString &atnName){
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    QTextStream out(&file);
    QDomDocument doc;
    QDomElement root, element;
    QDomText text;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version = \'1.0\' encoding = \'UTF-8\'");
    doc.appendChild(instruction);

    //project
    root = doc.createElement("project");
    root.setAttribute("name", atnName);
    doc.appendChild(root);

    element = doc.createElement("item");
    text = doc.createTextNode("模型简介");
    element.appendChild(text);
    element.setAttribute("flag", "viewOnly");
    root.appendChild(element);

    element = doc.createElement("node");
    element.setAttribute("name", "设计");
    element.setAttribute("flag", "design");
    root.appendChild(element);

    element = doc.createElement("node");
    element.setAttribute("name", "优化");
    element.setAttribute("flag", "optimization");
    root.appendChild(element);

    element = doc.createElement("node");
    element.setAttribute("name", "结果查看");
    element.setAttribute("flag", "result");
    root.appendChild(element);

    // /group
    // /designs /data   /project
    doc.save(out, 4);   //4 spaces
    return true;
}

void treeModel::parseProjectElement(const QDomElement &element){
    QDomNode child = element.firstChild();
    QDomElement childElement;
    while(! child.isNull()){
        childElement = child.toElement();
        if("node" == childElement.tagName()){
            parseNodeElement(childElement, treeRoot);
        }
        else if("item" == childElement.tagName()){
            parseItemElement(childElement, treeRoot);
        }
        child = child.nextSibling();
    }
}

void treeModel::parseNodeElement(const QDomElement &element, QStandardItem *parent){
    QStandardItem *item = new QStandardItem(IconMap[QStringLiteral("treeNode")], element.attribute("name"));
    if(element.hasAttribute("flag") && "design" == element.attribute("flag")){
        item->setData(MARK_NODE, ROLE_MARK);
        item->setData(MARK_NODE_DESIGN, ROLE_MARK_NODE);
    }
    else if(element.hasAttribute("flag") && "optimization" == element.attribute("flag")){
        item->setData(MARK_NODE, ROLE_MARK);
        item->setData(MARK_NODE_OPTIMIZATION, ROLE_MARK_NODE);
    }
    else{
        item->setData(MARK_NODE, ROLE_MARK);
        item->setData(MARK_NODE_RESULT, ROLE_MARK_NODE);
    }
    parent->appendRow(item);

    //traverse node
    QDomNode child = element.firstChild();
    QDomElement childElement;
    while(! child.isNull()){
        childElement = child.toElement();
        if("node" == childElement.tagName()){
            parseNodeElement(childElement, item);
        }
        else if("item" == childElement.tagName()){
            parseItemElement(childElement, item);
        }
        child = child.nextSibling();
    }
}

void treeModel::parseItemElement(const QDomElement &element, QStandardItem *parent){
    QStandardItem *item = new QStandardItem(IconMap[QStringLiteral("treeItem")], element.text());
    if(element.hasAttribute("flag") && "viewOnly" == element.attribute("flag")){
        item->setData(MARK_ITEM, ROLE_MARK);
        item->setData(MARK_ITEM_OPENFILE, ROLE_MARK_ITEM);
    }
    else{
        item->setData(MARK_ITEM, ROLE_MARK);
        item->setData(MARK_ITEM_ATNDESIGN, ROLE_MARK_ITEM);
    }
    parent->appendRow(item);
}

/*void treeModel::showTree(){
    //initIcon();
    //tModel = new QStandardItemModel(mTree);
    QStandardItem *itemPro = new QStandardItem(IconMap[QStringLiteral("treeNode")], QStringLiteral("工程名"));
    // set value and role
    itemPro->setData(MARK_PROJECT, ROLE_MARK);
    //itemPro->setData(MARK_FOLDER_GENERAL, ROLE_MARK_FOLDER);
    tModel->appendRow(itemPro);
    QStandardItem *itemModel = new QStandardItem(IconMap[QStringLiteral("treeItem")], QStringLiteral("模型简介"));
    itemModel->setData(MARK_ITEM, ROLE_MARK);
    itemModel->setData(MARK_ITEM_MODELVIEW, ROLE_MARK_ITEM);
    //itemModel->setFlags();
    itemPro->appendRow(itemModel);
    QStandardItem *itemDandO = new QStandardItem(IconMap[QStringLiteral("treeNode")], QStringLiteral("设计"));
    itemDandO->setData(MARK_FOLDER, ROLE_MARK);
    itemDandO->setData(MARK_FOLDER_ODESIGN, ROLE_MARK_FOLDER);
    itemPro->appendRow(itemDandO);
    QStandardItem *itemPerP = new QStandardItem(IconMap[QStringLiteral("treeItem")], QStringLiteral("性能指标"));
    itemPerP->setData(MARK_ITEM, ROLE_MARK);
    itemPerP->setData(MARK_ITEM_PERDESIGN, ROLE_MARK_ITEM);
    itemDandO->appendRow(itemPerP);
    //QStandardItem *itemAlgD = new QStandardItem(IconMap[QStringLiteral("treeItem")], QStringLiteral("算法设置"));
    //itemAlgD->setData(MARK_ITEM, ROLE_MARK);
    //itemAlgD->setData(MARK_ITEM_ALGDESIGN, ROLE_MARK_ITEM);
    //itemDandO->appendRow(itemAlgD);
    QStandardItem *itemModD = new QStandardItem(IconMap[QStringLiteral("treeNode")], QStringLiteral("模型设计"));
    itemModD->setData(MARK_FOLDER, ROLE_MARK);
    itemModD->setData(MARK_FOLDER_ODESIGN, ROLE_MARK_FOLDER);
    itemDandO->appendRow(itemModD);
    QStandardItem *itemAtnD = new QStandardItem(IconMap[QStringLiteral("treeItem")], QStringLiteral("设计1"));
    itemAtnD->setData(MARK_ITEM, ROLE_MARK);
    itemAtnD->setData(MARK_ITEM_ATNDESIGN, ROLE_MARK_ITEM);
    itemModD->appendRow(itemAtnD);
    QStandardItem *itemResult = new QStandardItem(IconMap[QStringLiteral("treeNode")], QStringLiteral("结果查看"));
    itemResult->setData(MARK_FOLDER, ROLE_MARK);
    itemResult->setData(MARK_FOLDER_RESULT, ROLE_MARK_FOLDER);
    itemDandO->appendRow(itemResult);
    mTree->setModel(tModel);
    mTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mTree->setContextMenuPolicy(Qt::CustomContextMenu);        //设置右键菜单    
    mTree->expandAll();
}*/

void treeModel::initMenu(){
    QAction* actClose = new QAction(QStringLiteral("关闭"), mTree);
    QAction* actDel = new QAction(QStringLiteral("删除"), mTree);
    connect(actDel, &QAction::triggered, this, &treeModel::slot_del);
    QAction* actHideAll = new QAction(QStringLiteral("全部折叠"), mTree);
    connect(actHideAll, &QAction::triggered, this, &treeModel::slot_hideAll);
    QAction* actShowAll = new QAction(QStringLiteral("全部展开"), mTree);
    connect(actShowAll, &QAction::triggered, this, &treeModel::slot_showAll);
    QAction* actAdd = new QAction(QStringLiteral("新增"), mTree);
    connect(actAdd, &QAction::triggered, this, &treeModel::slot_add);
    QAction* actRun = new QAction(QStringLiteral("运行"), mTree);
    connect(actRun, &QAction::triggered, this, &treeModel::slot_run);
    QAction* actOpenFile = new QAction(QStringLiteral("打开文件"), mTree);

    mProjectMenu->addAction(actClose);
    mProjectMenu->addAction(actDel);
    mProjectMenu->addSeparator();
    mProjectMenu->addAction(actHideAll);
    mProjectMenu->addAction(actShowAll);

    mAtnDesignMenu->addAction(actAdd);
    mAtnDesignMenu->addSeparator();
    mAtnDesignMenu->addAction(actHideAll);
    mAtnDesignMenu->addAction(actShowAll);

    mAtnOptimizationMenu->addAction(actAdd);
    mAtnOptimizationMenu->addSeparator();
    mAtnOptimizationMenu->addAction(actHideAll);
    mAtnOptimizationMenu->addAction(actShowAll);

    mResultMenu->addAction(actHideAll);
    mResultMenu->addAction(actShowAll);

    mItemViewMenu->addAction(actOpenFile);

    mItemMenu->addAction(actOpenFile);
    mItemMenu->addAction(actRun);
    mItemMenu->addAction(actDel);
}

QList<QStandardItem*> treeModel::getRoots(){
    QList<QStandardItem*> roots;
    for(int i = 0; i < tModel->rowCount(); ++ i){
        roots.append(tModel->item(i));
    }
    return roots;
}

QStandardItem* treeModel::getProNode(){
    QList<QStandardItem*> roots = getRoots();
    for(auto i = roots.begin(); i != roots.end(); ++ i){
        if((*i)->data(ROLE_MARK) == MARK_PROJECT){
            return (*i);
        }
    }
    return nullptr;
}

QList<QStandardItem*> treeModel::getFolderNode(){
    QList<QStandardItem*> folderNodes;
    QStandardItem* project = getProNode();
    if(project == nullptr){
        folderNodes.append(nullptr);
    }
    for(int i = 0; i < project->rowCount(); ++ i){
        QStandardItem* child = project->child(i);
        QVariant var = child->data(ROLE_MARK_NODE);
        if(! var.isValid()){
            continue;
        }
        folderNodes.append(child);
    }
    return folderNodes;
}

// slot function
//mouse right click
void treeModel::slot_customContextMenuRequested(const QPoint &pos){
    currentIndex = mTree->indexAt(pos);
    //qDebug() << currentIndex.data().toString();
    QVariant varNode = currentIndex.data(ROLE_MARK);
    QVariant varFolder = currentIndex.data(ROLE_MARK_NODE);
    QVariant varItem = currentIndex.data(ROLE_MARK_ITEM);
    int var2Int = varNode.toInt();
    int varItem2Int = varItem.toInt();
    if(varNode.isValid()){
        if(var2Int == MARK_PROJECT)
            mProjectMenu->exec(QCursor::pos()); //弹出右键菜单，菜单位置为光标位置
        else if(varFolder.isValid() && var2Int == MARK_NODE){
            if(varFolder.toInt() == MARK_NODE_DESIGN)
                mAtnDesignMenu->exec(QCursor::pos());
            else if(varFolder.toInt() == MARK_NODE_OPTIMIZATION)
                mAtnOptimizationMenu->exec(QCursor::pos());
            else
                mResultMenu->exec(QCursor::pos());
        }
        else if(varItem.isValid() && var2Int == MARK_ITEM){
            if(varItem2Int == MARK_ITEM_OPENFILE)
                mItemViewMenu->exec(QCursor::pos());
            else if(varItem2Int == MARK_ITEM_ATNDESIGN)
                mItemMenu->exec(QCursor::pos());
        }
    }
}

void treeModel::slot_showAll(){
    mTree->expandAll();
}

void treeModel::slot_hideAll(){
    mTree->collapseAll();
}

void treeModel::slot_add(){
    //qDebug() << currentIndex.data().toString();
    QStandardItemModel *itemModel = const_cast<QStandardItemModel *>(
                static_cast<const QStandardItemModel *>(currentIndex.model()));
    QStandardItem *item = itemModel->itemFromIndex(currentIndex);
    QVariant varNode = currentIndex.data(ROLE_MARK_NODE);
    if(varNode.isValid()){
        if(MARK_NODE_DESIGN == varNode.toInt()){            
            //designWizard *wizard = new designWizard(confManage->readPath("MODELVARIABLES"));
            designWizard *wizard = new designWizard(QString("%1/%2_conf.json").arg(sysParam["WorkingProjectPath"])
                    .arg(global::getInfoFromRel("Problem")));
            if(wizard->exec() == 1){
                QStandardItem *child = new QStandardItem(
                            IconMap[QStringLiteral("treeItem")], QString("设计%1").arg(item->rowCount()+1));
                child->setData(MARK_ITEM, ROLE_MARK);
                child->setData(MARK_ITEM_ATNDESIGN, ROLE_MARK_ITEM);
                item->appendRow(child);
            }
        }
        else if(MARK_NODE_OPTIMIZATION == varNode.toInt()){}
    }
}

void treeModel::slot_run(){
    Run run;
    run.go();
}

void treeModel::slot_del(){
    //QStandardItemModel *itemM
}
