#include "atnlibrary.h"
#include "global.h"

atnLibrary::atnLibrary(QString sql, treeModel *mTreeModel, QWidget *parent) : QWidget(parent){
    this->mTreeModel = mTreeModel;
    tableView = new QTableWidget();
    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    failedSearch = new QLabel;
    itemMenu = new QMenu;
    atnDockWH = 1148;
    numOfTableCol = 6;
    initMenu();
    showInfo();
    arrangeAtn(setAtnList(sql), atnDockWH, numOfTableCol);
    //QMessageBox::information(this, "infomation", "atnlibrary:"+QString::number(geometry().width()));
    //qDebug() << sizeHint().width() << "," << sizeHint().height();
    connect(tableView, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(slot_tableCellDoubleClick(int,int)));
    connect(tableView, SIGNAL(cellPressed(int,int)), this, SLOT(slot_cellPressed(int,int)));
    connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_customContextMenuRequested(QPoint)));
}

void atnLibrary::showInfo(){
    //search result is Null
    failedSearch->setText("搜索结果为空，请重新搜索！");
    QFont *font = new QFont;
    font->setBold(true);
    font->setPixelSize(30);
    failedSearch->setFont(*font);
    failedSearch->setAlignment(Qt::AlignCenter);

    //find something
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setVisible(false);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void atnLibrary::arrangeAtn(QList<antennaCell *> atnList, int tabWH, int numOfCol){
    tableView->clear();
    int numOfAtn = atnList.size();
    numOfTableCol = numOfCol;
    if(numOfAtn != 0){
        if(numOfAtn < numOfTableCol){
            numOfTableCol = numOfAtn;
        }
        QList<int> atnWH = setAtnWidth(tabWH, numOfTableCol);
        int numOfRow = numOfAtn / numOfTableCol;
        numOfRow = (numOfAtn % numOfTableCol) == 0 ? numOfRow : (numOfRow + 1);
        tableView->setColumnCount(numOfTableCol);
        tableView->setRowCount(numOfRow);
        for(int i = 0; i < numOfRow; ++ i){
            tableView->setRowHeight(i, CELLATNHT);
        }
        for(int j = 0; j < numOfTableCol; ++ j){
            tableView->setColumnWidth(j, atnWH.at(j));
        }
        for(int k = 0; k < numOfAtn; ++ k){
            tableView->setCellWidget(k / numOfTableCol, k % numOfTableCol, atnList.at(k));
        }
    }
    QLabel *plusPhoto = new QLabel;
    QPixmap plusMap = QPixmap("./images/plus.png");
    plusPhoto->setPixmap(plusMap);
    tableView->setCellWidget(numOfAtn / numOfTableCol, numOfAtn % numOfTableCol, plusPhoto);
}

// set antenna width
QList<int> atnLibrary::setAtnWidth(int width, int colNum){
    QList<int> atnWidth;
    for(int i = 0; i < colNum; ++i){
        atnWidth.append(width / colNum);
    }
    int restPixNum = width % colNum;
    for(int j = 0; j < restPixNum; ++j){
        ++ atnWidth[colNum-1-j];
    }
    return atnWidth;
}

QList<antennaCell *> atnLibrary::setAtnList(QString selectSql){
    QList<antennaCell *> atnCellList;
    if(selectSql != NULL){
        //sqliteManage* mSqlManage = new sqliteManage();
        QSqlQuery sqlQuery;
        sqlQuery.prepare(selectSql);
        if(!sqlQuery.exec(selectSql)){
            qDebug()<< sqlQuery.lastError();
        }
        else{
            while(sqlQuery.next()){
                antennaCell* atnCellTemp = new antennaCell(sqlQuery.value("pModelPath").toString(), sqlQuery.value("pName").toString());
                atnCellList.append(atnCellTemp);
            }
        }
        //delete mSqlManage;
    }
    return atnCellList;
}

void atnLibrary::initMenu(){
    actNew = new QAction(QStringLiteral("新建工程"), this);
    connect(actNew, &QAction::triggered, this, &atnLibrary::slot_newProject);
    actProperty = new QAction(QStringLiteral("属性"), this);
    connect(actProperty, &QAction::triggered, this, &atnLibrary::slot_property);

    itemMenu->addAction(actNew);
    itemMenu->addAction(actProperty);
}

int atnLibrary::getAtnDockWH(){
    return atnDockWH;
}

QTableWidget* atnLibrary:: getTableWidget() const{
    return tableView;
}

QLabel* atnLibrary::getLabel() const{
    return failedSearch;
}

void atnLibrary::slot_reSizeSlot(int row, int column){
    int x = 0, y = 0, n = 0;
    for(int i = 0; i < row; ++ i){
        y = i * (MBNTICON_HT+MBNTDIS) + MBNTDIS;
        for(int j = 0; j < column; ++ j){
            x = j * (MBNTICON_WH+MBNTDIS) + MBNTDIS;
            if(n >= NUMOFANTENNA) break;
            //mListBtn.at(n++)->move(x, y);
        }
    }
}

void atnLibrary::slot_showProTree(bool isShow){
    //isShowTree = isShow;
    //emit signal_sendShowPro(isShowTree);
}

void atnLibrary::slot_tableCellDoubleClick(int row, int col){
    int index = numOfTableCol * row + col;
    //qDebug() << index;
    QWidget* currentWidget = tableView->cellWidget(row, col);
    if(currentWidget){
        antennaCell* cellTab = static_cast<antennaCell* >(currentWidget);
        atnName = cellTab->getAtnName();
        projectWizard* wizard = new projectWizard(atnName);
        if(wizard->exec() == 1){           
            QString workingPath =  sysParam["WorkingProjectPath"];
            QString projectName = global::getProjectName();
            //qDebug() << "atnlibrary:WorkingProjectPath=" << workingPath << "pro=" << projectName;
            mTreeModel->writeXMLFile(QString("%1/%2.xml").arg(workingPath).arg(projectName), atnName);
            mTreeModel->parseXML(QString("%1/%2.xml").arg(workingPath).arg(projectName));
        }
    }
}

//when the mouse button press
void atnLibrary::slot_cellPressed(int row, int col){
    QWidget* currentWidget = tableView->cellWidget(row, col);
    if(currentWidget){
        antennaCell* cellTab = static_cast<antennaCell* >(currentWidget);
        atnName = cellTab->getAtnName();
    }
}

void atnLibrary::slot_customContextMenuRequested(QPoint pos){
    if(tableView->indexAt(pos).model())
        itemMenu->exec(QCursor::pos());
}

void atnLibrary::slot_newProject(){
    projectWizard* wizard = new projectWizard(atnName);
    if(wizard->exec() == 1){
        QString workingPath =  sysParam["WorkingProjectPath"];
        QString projectName = global::getProjectName();
        mTreeModel->writeXMLFile(QString("%1/%2.xml").arg(workingPath).arg(projectName), atnName);
        mTreeModel->parseXML(QString("%1/%2.xml").arg(workingPath).arg(projectName));
    }
}

void atnLibrary::slot_property(){
    modelFile *mf = new modelFile(atnName);
    mf->show();
}
