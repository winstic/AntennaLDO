#include "treeModel.h"
#include <QDebug>

treeModel::treeModel(QTreeView* m_tree) : mTree(m_tree){
    //QStandardItemModel* tModel = new QStandardItemModel(mTree);    
    mProjectMenu = new QMenu();
    mAtnDesignMenu = new QMenu();
    mAtnOptimizeMenu = new QMenu();
    mItemDesignMenu = new QMenu();
    mItemOptimizeMenu = new QMenu();
    mItemViewMenu = new QMenu();
    mResultMenu = new QMenu();
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
    //design run
    actDesignRun = new QAction(QStringLiteral("运行"), mTree);
    connect(actDesignRun, &QAction::triggered, this, &treeModel::slot_designRun);
    //optimize run
    actOptimizeRun = new QAction(QStringLiteral("运行"), mTree);
    connect(actOptimizeRun, &QAction::triggered, this, &treeModel::slot_optimizeRun);
    actInterrupt = new QAction(QStringLiteral("暂停"), mTree);
    connect(actInterrupt, &QAction::triggered, this, &treeModel::slot_interrupt);
    actDesignStop = new QAction(QStringLiteral("终止"), mTree);
    connect(actDesignStop, &QAction::triggered, this, &treeModel::slot_designStop);
    actOptimizeStop = new QAction(QStringLiteral("终止"), mTree);
    connect(actOptimizeStop, &QAction::triggered, this, &treeModel::slot_optimizeStop);
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
    mItemDesignMenu->addAction(actDesignRun);
    mItemDesignMenu->addAction(actInterrupt);
    mItemDesignMenu->addAction(actDesignStop);
    mItemDesignMenu->addSeparator();
    mItemDesignMenu->addAction(actDel);
    mItemDesignMenu->addAction(actShowResult);

    mItemOptimizeMenu->addAction(actModifyOptimizeVar);
    mItemOptimizeMenu->addSeparator();
    mItemOptimizeMenu->addAction(actOptimizeRun);
    mItemOptimizeMenu->addAction(actInterrupt);
    mItemOptimizeMenu->addAction(actOptimizeStop);
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
    QString atnProName = global::getInfoFromRel("Problem");
    QString atnProType = global::getInfoFromRel("ProType");
    if(varNode.isValid()){
        if(MARK_NODE_DESIGN == varNode.toInt()){
            QString workingDir = sysParam["WorkingProjectPath"];
            QString jsonPath = QString("%1/%2_conf.json").arg(workingDir).arg(atnProName);
            QJsonObject obj = parseJson::getJsonObj(jsonPath);
            if(obj.isEmpty()){
                QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:389: error: Cannot parse jsonFile %1").arg(jsonPath));
                return;
            }
            designWizard *wizard = new designWizard(obj,this);
            //wizard->setAttribute(Qt::WA_DeleteOnClose);
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
                //copy files(.json, module file) in designDir from projectDir
                bool isSuccess = false;
                proType atntype = (proType)atnProType.toInt();
                if( global::copyFile(QString("%1/%2_conf.json").arg(workingDir).arg(atnProName), QString("%1/%2_conf.json").arg(designDir).arg(atnProName)) ){
                    if( atntype == hfss)
                        isSuccess = global::copyFile(QString("%1/%2_design.vbs").arg(workingDir).arg(atnProName), QString("%1/%2_design.vbs").arg(designDir).arg(atnProName));
                    else
                        isSuccess = true;
                }

                if(!isSuccess){
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:431: error: create design module failed!"));
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
    QString atnProName = global::getInfoFromRel("Problem");
    QString atnProType = global::getInfoFromRel("ProType");
    if(varNode.isValid()){
        if(MARK_NODE_OPTIMIZE == varNode.toInt()){
            QString workingDir = sysParam["WorkingProjectPath"];
            QString jsonPath = QString("%1/%2_conf.json").arg(workingDir).arg(atnProName);
            QJsonObject obj = parseJson::getJsonObj(jsonPath);
            if(obj.isEmpty()){
                QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:457: error: Cannot parse jsonFile %1").arg(jsonPath));
                return;
            }
            optimizeWizard *wizard = new optimizeWizard(obj,this);
            //wizard->setAttribute(Qt::WA_DeleteOnClose);
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
                bool isSuccess = false;
                proType atntype = (proType)atnProType.toInt();
                isSuccess = global::copyFile(QString("%1/%2_conf.json").arg(workingDir).arg(atnProName), QString("%1/%2_conf.json").arg(optimizeDir).arg(atnProName)) &&
                        global::copyFile(QString("%1/global_conf.json").arg(workingDir), QString("%1/global_conf.json").arg(optimizeDir)) &&
                        global::copyFile(QString("%1/start.json").arg(workingDir), QString("%1/start.json").arg(optimizeDir)) &&
                        global::copyFile(QString("%1/algorithm_conf.json").arg(workingDir), QString("%1/algorithm_conf.json").arg(optimizeDir));

                sysParam["CurrentOptimizePath"] = optimizeDir;      //save current optimize path in global variable
                dir->mkdir(QString("%1/outfilepath").arg(optimizeDir));
                dir->mkdir(QString("%1/outhfsspath").arg(optimizeDir));
                if( isSuccess && (atntype == feko) )
                    isSuccess = global::copyFile(QString("%1/%2.cfx").arg(workingDir).arg(atnProName), QString("%1/outfilepath/%2.cfx").arg(optimizeDir).arg(atnProName));

                if( !isSuccess ){
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:459: error: create optimize module failed!"));
                    dir->rmdir(optimizeDir);
                    return;
                }
                qDebug() << "CurrentOptimizePath: " << sysParam["CurrentOptimizePath"];
                if(!(wizard->update2JsonFile() && updateXMLFile(QString("%1/%2.xml").arg(workingDir).arg(global::getProjectName()), item, child)))
                    QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:467: error: update module files failed!"));
            }
        }
    }
}

void treeModel::slot_openFile(){
    QString atnProName = global::getInfoFromRel("Problem");
    modelFile *mf = new modelFile(atnProName,this);
    //mf->setAttribute(Qt::WA_DeleteOnClose);
    //mf->setModal(true);
    mf->exec();
}

void treeModel::slot_modifyDesignVar(){
    QString atnProName = global::getInfoFromRel("Problem");
    QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentDesignPath"]).arg(atnProName);
    QJsonObject obj = parseJson::getJsonObj(jsonPath);
    if(obj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:425: error: Cannot parse jsonFile %1").arg(jsonPath));
        return;
    }
    designTab *dTab = new designTab(obj,this);
    //dTab->setAttribute(Qt::WA_DeleteOnClose);
    //dTab->setModal(true);
    dTab->exec();
}

void treeModel::slot_modifyOptimizeVar(){
    QString atnProName = global::getInfoFromRel("Problem");
    QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentOptimizePath"]).arg(atnProName);
    QJsonObject obj = parseJson::getJsonObj(jsonPath);
    if(obj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("treeModel.cpp:425: error: Cannot parse jsonFile %1").arg(jsonPath));
        return;
    }
    optimizeTab *otab = new optimizeTab(obj,this);
    //otab->setAttribute(Qt::WA_DeleteOnClose);
    //otab->setModal(true);
    otab->exec();
}

void treeModel::slot_designRun(){
    designRun *dRun = new designRun();
    dRun->start();
}

void treeModel::slot_optimizeRun(){
    optimizeRun *oRun = new optimizeRun();
    oRun->start();
}

void treeModel::slot_interrupt(){}

void treeModel::slot_designStop(){}

void treeModel::slot_optimizeStop(){
    QDir dir(QDir::currentPath());
    QString ostopPath = QString("%1/DEA4AD/trunk/end.bat").arg(dir.path());
    //QString ostopPath = QString("./DEA4AD/trunk/end.bat");
    qDebug() << ostopPath;
    QProcess p(0);
    //"/c" mean close cmd window after execute .bat file.
    p.execute("cmd.exe", QStringList() << "/c" << ostopPath);
    p.waitForFinished();
    qDebug() << p.readAllStandardOutput();
}

void treeModel::slot_showResult(){
    QString atnProName = global::getInfoFromRel("Problem");
    QString hfssPath = QString("%1/%2.hfss").arg(sysParam["CurrentDesignPath"]).arg(atnProName);
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
