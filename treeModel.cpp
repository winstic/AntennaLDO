#include "treeModel.h"
#include <QDebug>

treeModel::treeModel(QTreeView* m_tree){
    //QStandardItemModel* tModel = new QStandardItemModel(mTree);
    mTree = m_tree;
    mProjectMenu = new QMenu;
    mAtnDesignMenu = new QMenu;
    mAtnOptimizeMenu = new QMenu;
    mItemDesignMenu = new QMenu;
    mItemOptimizeMenu = new QMenu;
    mItemViewMenu = new QMenu;
    mResultMenu = new QMenu;
    //actRightClick = nullptr;
    initMenu();
    initIcon();    
    connect(mTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slot_customContextMenuRequested(const QPoint&)));
    connect(mTree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_doubleClick(QModelIndex)));
}

void treeModel::initIcon(){
    IconMap[QStringLiteral("treeNode")] = QIcon(QStringLiteral("./images/node.png"));
    IconMap[QStringLiteral("treeItem")] = QIcon(QStringLiteral("./images/item.png"));
}

bool treeModel::writeXMLFile(const QString &fileName, const QString &atnName){
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
    element.setAttribute("flag", "optimize");
    root.appendChild(element);

    element = doc.createElement("node");
    element.setAttribute("name", "结果查看");
    element.setAttribute("flag", "result");
    root.appendChild(element);

    // /group
    // /designs /data   /project
    out.setCodec("UTF-8");
    doc.save(out, 4);   //4 spaces
    return true;
}

bool treeModel::updateXMLFile(const QString &fileName, const QStandardItem *item, const QStandardItem *child){
    //!get xml root node
    QFile inFile(fileName);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:72: error: Cannot read file %1").arg(fileName));
        return false;
    }
    QDomDocument doc;
    QString error;
    int row, column;
    if(!doc.setContent(&inFile, false, &error, &row, &column)){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:79: error: Parse error at row %1, column %2: %3")
                              .arg(row).arg(column).arg(error));
        return false;
    }
    inFile.close();
    QDomElement xmlRoot = doc.documentElement();
    if("project" != xmlRoot.tagName()){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:86: error: Not a project file"));
        return false;
    }
    //!
    //QString childStr = child->text();
    QDomNode rootChild = xmlRoot.firstChild();
    QDomElement rootChildElement;
    while(! rootChild.isNull()){
        rootChildElement = rootChild.toElement();
        if(("node" == rootChildElement.tagName()) && rootChildElement.hasAttribute("flag")){
            if( (MARK_NODE_DESIGN == item->data(ROLE_MARK_NODE) && "design" == rootChildElement.attribute("flag")) ||
                    (MARK_NODE_OPTIMIZE == item->data(ROLE_MARK_NODE) && "optimize" == rootChildElement.attribute("flag"))){
                QDomElement designElement = doc.createElement("item");
                QDomText designText = doc.createTextNode(child->text());
                designElement.appendChild(designText);
                designElement.setAttribute("id", rootChildElement.childNodes().count()+1);
                rootChildElement.appendChild(designElement);
                break;
            }
        }
        rootChild = rootChild.nextSibling();
    }


    QFile outfile(fileName);
    if(!outfile.open(QIODevice::WriteOnly))
        return false;
    QTextStream out(&outfile);
    out.setCodec("utf-8");
    doc.save(out, 4);
    return true;
}

bool treeModel::parseXML(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:120: error: Cannot read file %1").arg(fileName));
        return false;
    }
    QDomDocument doc;
    QString error;
    int row, column;
    if(!doc.setContent(&file, false, &error, &row, &column)){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:127: error: Parse error at row %1, column %2: %3")
                              .arg(row).arg(column).arg(error));
        return false;
    }
    file.close();
    QDomElement xmlRoot = doc.documentElement();
    if("project" != xmlRoot.tagName()){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:134: error: Not a project file"));
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
    else if(element.hasAttribute("flag") && "optimize" == element.attribute("flag")){
        item->setData(MARK_NODE, ROLE_MARK);
        item->setData(MARK_NODE_OPTIMIZE, ROLE_MARK_NODE);
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
    else if(MARK_NODE_DESIGN == parent->data(ROLE_MARK_NODE)){
        item->setData(MARK_ITEM, ROLE_MARK);
        item->setData(MARK_ITEM_ATNDESIGN, ROLE_MARK_ITEM);
    }
    else if(MARK_NODE_OPTIMIZE == parent->data(ROLE_MARK_NODE)){
        item->setData(MARK_ITEM, ROLE_MARK);
        item->setData(MARK_ITEM_ATNOPTIMIZE, ROLE_MARK_ITEM);
    }
    parent->appendRow(item);
}

void treeModel::initMenu(){
    actClose = new QAction(QStringLiteral("关闭"), mTree);
    actDel = new QAction(QStringLiteral("删除"), mTree);
    connect(actDel, &QAction::triggered, this, &treeModel::slot_del);
    actHideAll = new QAction(QStringLiteral("全部折叠"), mTree);
    connect(actHideAll, &QAction::triggered, this, &treeModel::slot_hideAll);
    actShowAll = new QAction(QStringLiteral("全部展开"), mTree);
    connect(actShowAll, &QAction::triggered, this, &treeModel::slot_showAll);
    actAddDesign = new QAction(QStringLiteral("添加设计"), mTree);
    connect(actAddDesign, &QAction::triggered, this, &treeModel::slot_addDesign);
    actAddOptimize = new QAction(QStringLiteral("添加优化"), mTree);
    connect(actAddOptimize, &QAction::triggered, this, &treeModel::slot_addOptimize);
    actRun = new QAction(QStringLiteral("运行"), mTree);
    connect(actRun, &QAction::triggered, this, &treeModel::slot_run);
    actInterrupt = new QAction(QStringLiteral("暂停"), mTree);
    connect(actInterrupt, &QAction::triggered, this, &treeModel::slot_interrupt);
    actStop = new QAction(QStringLiteral("终止"), mTree);
    connect(actStop, &QAction::triggered, this, &treeModel::slot_stop);
    actOpenFile = new QAction(QStringLiteral("打开"), mTree);
    connect(actOpenFile, &QAction::triggered, this, &treeModel::slot_openFile);
    actModifyDesignVar = new QAction(QStringLiteral("修改参数"), mTree);
    connect(actModifyDesignVar, &QAction::triggered, this, &treeModel::slot_modifyDesignVar);
    actModifyOptimizeVar = new QAction(QStringLiteral("修改参数"), mTree);
    connect(actModifyOptimizeVar, &QAction::triggered, this, &treeModel::slot_modifyOptimizeVar);
    actShowResult = new QAction(QStringLiteral("结果查看"), mTree);
    //actShowResult->setEnabled(false);
    connect(actShowResult, &QAction::triggered, this, &treeModel::slot_showResult);

    mProjectMenu->addAction(actClose);
    mProjectMenu->addAction(actDel);
    mProjectMenu->addSeparator();
    mProjectMenu->addAction(actHideAll);
    mProjectMenu->addAction(actShowAll);

    mAtnDesignMenu->addAction(actAddDesign);

    mAtnOptimizeMenu->addAction(actAddOptimize);

    mItemViewMenu->addAction(actOpenFile);

    mItemDesignMenu->addAction(actModifyDesignVar);
    mItemDesignMenu->addSeparator();
    mItemDesignMenu->addAction(actRun);
    mItemDesignMenu->addAction(actInterrupt);
    mItemDesignMenu->addAction(actStop);
    mItemDesignMenu->addSeparator();
    mItemDesignMenu->addAction(actDel);
    mItemDesignMenu->addAction(actShowResult);

    mItemOptimizeMenu->addAction(actModifyOptimizeVar);
    mItemOptimizeMenu->addSeparator();
    mItemOptimizeMenu->addAction(actRun);
    mItemOptimizeMenu->addAction(actInterrupt);
    mItemOptimizeMenu->addAction(actStop);
    mItemOptimizeMenu->addSeparator();
    mItemOptimizeMenu->addAction(actDel);
    mItemOptimizeMenu->addAction(actShowResult);
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
            else if(varFolder.toInt() == MARK_NODE_OPTIMIZE)
                mAtnOptimizeMenu->exec(QCursor::pos());
            else
                mResultMenu->exec(QCursor::pos());
        }
        else if(varItem.isValid() && var2Int == MARK_ITEM){
            if(varItem2Int == MARK_ITEM_OPENFILE)
                mItemViewMenu->exec(QCursor::pos());
            else if(varItem2Int == MARK_ITEM_ATNDESIGN){
                //QStandardItemModel *itemModel = const_cast<QStandardItemModel *>(
                            //static_cast<const QStandardItemModel *>(currentIndex.model()));
                //QString designName = itemModel->itemFromIndex(currentIndex)->text();
                int designIndex = currentIndex.row() + 1;
                //update current design path
                sysParam["CurrentDesignPath"] = QString("%1/design%2").arg(sysParam["WorkingProjectPath"]).arg(designIndex);
                mItemDesignMenu->exec(QCursor::pos());
            }
            else if(varItem2Int == MARK_ITEM_ATNOPTIMIZE){
                int optimizeIndex = currentIndex.row() + 1;
                sysParam["CurrentOptimizePath"] = QString("%1/optimize%2").arg(sysParam["WorkingProjectPath"]).arg(optimizeIndex);
                mItemOptimizeMenu->exec(QCursor::pos());
            }
        }
    }
}

void treeModel::slot_doubleClick(QModelIndex itemIndex){
    QVariant varItem = itemIndex.data(ROLE_MARK_ITEM);
    int doIndex = itemIndex.row() + 1;
    if(varItem.isValid()){
        int item2int = varItem.toInt();
        if(item2int == MARK_ITEM_ATNDESIGN){
            sysParam["CurrentDesignPath"] = QString("%1/design%2").arg(sysParam["WorkingProjectPath"]).arg(doIndex);
            slot_modifyDesignVar();
        }
        else if(item2int == MARK_ITEM_ATNOPTIMIZE){
            sysParam["CurrentOptimizePath"] = QString("%1/optimize%2").arg(sysParam["WorkingProjectPath"]).arg(doIndex);
            slot_modifyOptimizeVar();
        }
        else if(item2int == MARK_ITEM_OPENFILE)
            slot_openFile();
    }
}

void treeModel::slot_showAll(){
    mTree->expandAll();
}

void treeModel::slot_hideAll(){
    mTree->collapseAll();
}

void treeModel::slot_addDesign(){
    //qDebug() << currentIndex.data().toString();
    QStandardItemModel *itemModel = const_cast<QStandardItemModel *>(
                static_cast<const QStandardItemModel *>(currentIndex.model()));
    QStandardItem *item = itemModel->itemFromIndex(currentIndex);
    QVariant varNode = currentIndex.data(ROLE_MARK_NODE);
    if(varNode.isValid()){
        if(MARK_NODE_DESIGN == varNode.toInt()){
            QString workingDir = sysParam["WorkingProjectPath"];
            QString atnName = global::getInfoFromRel("Problem");
            QString jsonPath = QString("%1/%2_conf.json").arg(workingDir).arg(atnName);
            QJsonObject obj = parseJson::getJsonObj(jsonPath);
            if(obj.isEmpty()){
                QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:389: error: Cannot parse jsonFile %1").arg(jsonPath));
                return;
            }
            designWizard *wizard = new designWizard(obj);
            if(wizard->exec() == 1){
                QString designName = QString("设计%1").arg(item->rowCount()+1);
                QDir *dir = new QDir();
                QString designDir = QString("%1/design%2").arg(workingDir).arg(item->rowCount()+1);

                QStandardItem *child = new QStandardItem(
                            IconMap[QStringLiteral("treeItem")], designName);
                child->setData(MARK_ITEM, ROLE_MARK);
                child->setData(MARK_ITEM_ATNDESIGN, ROLE_MARK_ITEM);
                item->appendRow(child);
                dir->mkdir(designDir);
                //copy files(.json, .vbs,) in designDir from projectDir
                if(! global::copyFile(QString("%1/%2_conf.json").arg(workingDir).arg(atnName), QString("%1/%2_conf.json").arg(designDir).arg(atnName)) ||
                        ! global::copyFile(QString("%1/%2_design.vbs").arg(workingDir).arg(atnName), QString("%1/%2_design.vbs").arg(designDir).arg(atnName)) ){
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:411: error: create design module failed!"));
                    dir->rmdir(designDir);
                    return;
                }
                sysParam["CurrentDesignPath"] = designDir;      //save current design path in global variable
                qDebug() << "CurrentDesignPath: " << sysParam["CurrentDesignPath"];
                if(!(wizard->update2JsonFile() && updateXMLFile(QString("%1/%2.xml").arg(workingDir).arg(global::getProjectName()), item, child))){
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:421: error: update module files failed!"));
                }
            }
        }
    }
}

void treeModel::slot_addOptimize(){
    QStandardItemModel *itemModel = const_cast<QStandardItemModel *>(
                static_cast<const QStandardItemModel *>(currentIndex.model()));
    QStandardItem *item = itemModel->itemFromIndex(currentIndex);
    QVariant varNode = currentIndex.data(ROLE_MARK_NODE);
    if(varNode.isValid()){
        if(MARK_NODE_OPTIMIZE == varNode.toInt()){
            QString workingDir = sysParam["WorkingProjectPath"];
            QString atnName = global::getInfoFromRel("Problem");
            QString jsonPath = QString("%1/%2_conf.json").arg(workingDir).arg(atnName);
            QJsonObject obj = parseJson::getJsonObj(jsonPath);
            if(obj.isEmpty()){
                QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:457: error: Cannot parse jsonFile %1").arg(jsonPath));
                return;
            }
            optimizeWizard *wizard = new optimizeWizard(obj);
            if(wizard->exec() == 1){                
                QString optimizeName = QString("优化%1").arg(item->rowCount()+1);
                QDir *dir = new QDir();
                QString optimizeDir = QString("%1/optimize%2").arg(workingDir).arg(item->rowCount()+1);

                QStandardItem *child = new QStandardItem(
                            IconMap[QStringLiteral("treeItem")], optimizeName);
                child->setData(MARK_ITEM, ROLE_MARK);
                child->setData(MARK_ITEM_ATNOPTIMIZE, ROLE_MARK_ITEM);
                item->appendRow(child);
                dir->mkdir(optimizeDir);
                //copy files(.json..,) in optimizeDir from projectDir
                QString algName = global::getInfoFromRel("Algorithm");
                if(! global::copyFile(QString("%1/%2_conf.json").arg(workingDir).arg(atnName), QString("%1/%2_conf.json").arg(optimizeDir).arg(atnName)) ||
                        ! global::copyFile(QString("%1/global_conf.json").arg(workingDir), QString("%1/global_conf.json").arg(optimizeDir)) ||
                        ! global::copyFile(QString("%1/%2_conf.json").arg(workingDir).arg(algName), QString("%1/%2_conf.json").arg(optimizeDir).arg(algName)) ){
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:459: error: create optimize module failed!"));
                    dir->rmdir(optimizeDir);
                    return;
                }
                sysParam["CurrentOptimizePath"] = optimizeDir;      //save current optimize path in global variable
                qDebug() << "CurrentOptimizePath: " << sysParam["CurrentOptimizePath"];
                if(!(wizard->update2JsonFile() && updateXMLFile(QString("%1/%2.xml").arg(workingDir).arg(global::getProjectName()), item, child)))
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:467: error: update module files failed!"));
            }
        }
    }
}

void treeModel::slot_openFile(){
    QString antennaName = global::getInfoFromRel("Problem");
    modelFile *mf = new modelFile(antennaName);
    mf->setModal(true);
    mf->show();
}

void treeModel::slot_modifyDesignVar(){
    QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentDesignPath"]).arg(global::getInfoFromRel("Problem"));
    QJsonObject obj = parseJson::getJsonObj(jsonPath);
    if(obj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:425: error: Cannot parse jsonFile %1").arg(jsonPath));
        return;
    }
    designTab *dTab = new designTab(obj);
    dTab->setModal(true);
    dTab->show();
}

void treeModel::slot_modifyOptimizeVar(){
    QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentOptimizePath"]).arg(global::getInfoFromRel("Problem"));
    QJsonObject obj = parseJson::getJsonObj(jsonPath);
    if(obj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:425: error: Cannot parse jsonFile %1").arg(jsonPath));
        return;
    }
    optimizeTab *otab = new optimizeTab(obj);
    otab->setModal(true);
    otab->show();
}

void treeModel::slot_run(){
    ThreadRun *ProThread = new ThreadRun(flagDesign);
    ProThread->start();
}

void treeModel::slot_interrupt(){}

void treeModel::slot_stop(){}

void treeModel::slot_showResult(){
    QString hfssPath = QString("%1/%2.hfss").arg(sysParam["CurrentDesignPath"]).arg(global::getInfoFromRel("Problem"));
    QProcess p(0);;
    int isOK  = p.execute("hfss", QStringList() << hfssPath);
    if(isOK != 0)
       QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:451: error: Cannot execute hfssPath"));
    p.waitForFinished();
    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
}

void treeModel::slot_del(){
    //QStandardItemModel *itemM
}
