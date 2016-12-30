#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), isClosedSubmdi(false){
    ui->setupUi(this);
    //list all file in current work dir
    /*QDir dir(QDir::currentPath());
    qDebug() << "dir start " << dir.path() << " dir end";
    QStringList infolist = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for(int i=0; i<infolist.size(); i++)
        qDebug() << infolist.at(i);*/
    //delete centralWidget
    QWidget *p = takeCentralWidget();
    if(p){
        delete p;
    }
    //allow nesting dock
    setDockNestingEnabled(true);
    init_docks();
    layoutDock();
    createActions();
}

void MainWindow::init_docks(){
    //Init State Dock
    QLabel *stateLabel = new QLabel;
    stateDock = new QDockWidget("状态");
    setDockSize(stateDock, -1, 100);
    stateDock->setWidget(stateLabel);

    //Init Print Dock
    QTextEdit *outputEdit = new QTextEdit;
    printDock = new QDockWidget("输出");
    printDock->setWidget(outputEdit);

    //Init Project Tree Dock
    proTree = new QTreeView;
    mTreeModel = new treeModel(proTree);
    proTreeDock = new QDockWidget("项目管理");
    proTreeDock->setWidget(proTree);
    //connect(proTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slot_customContextMenuRequested(const QPoint&)));

    //Init Antenna Library Dock
    atnLibrary* atnTable = new atnLibrary("select pModelPath, pName from antennaProblem;", mTreeModel);
    antLibraryDock = new QDockWidget("Antenna Model");
    setDockSize(antLibraryDock, 1148);
    antLibraryDock->setWidget(atnTable->getTableWidget());

    //init Antenna Search Dock
    searchAtnTable = new atnLibrary(NULL, mTreeModel);
    searchDock = new QDockWidget("Search Result");
    searchDock->setWidget(searchAtnTable->getLabel());
}

void MainWindow::layoutDock(){
    addDockWidget(Qt::LeftDockWidgetArea, proTreeDock);
    addDockWidget(Qt::RightDockWidgetArea, antLibraryDock);
    addDockWidget(Qt::BottomDockWidgetArea, stateDock);
    tabifyDockWidget(antLibraryDock, searchDock);
    tabifyDockWidget(stateDock, printDock);

    stateDock->hide();
    printDock->hide();
    searchDock->hide();
}

void MainWindow::createActions(){
    //File Menu Start
    QMenu *fileMenu = menuBar()->addMenu(QStringLiteral("文件&(F)"));
    QToolBar *fileToolBar = addToolBar(QStringLiteral("文件"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon("./images/new.png"));
    QAction *newAction = new QAction(newIcon, QStringLiteral("新建&(N)"), this);
    newAction->setShortcuts(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::slot_NewProject);
    fileMenu->addAction(newAction);
    fileToolBar->addAction(newAction);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon("./images/open.png"));
    QAction *openAction = new QAction(openIcon, QStringLiteral("打开&(O)"), this);
    openAction->setShortcuts(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::slot_OpenProject);
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);
    fileMenu->addSeparator();

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon("./images/save.png"));
    QAction *saveAction = new QAction(saveIcon, QStringLiteral("保存&(S)"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::slot_Save);
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAction = new QAction(saveAsIcon, QStringLiteral("另存为"), this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::slot_SaveAs);
    fileMenu->addAction(saveAsAction);

    const QIcon saveAllIcon = QIcon::fromTheme("document-save-all", QIcon("./images/save_all.png"));
    QAction *saveAllAction = new QAction(saveAllIcon, QStringLiteral("全部保存"), this);
    connect(saveAllAction, &QAction::triggered, this, &MainWindow::slot_SaveAll);
    fileMenu->addAction(saveAllAction);
    fileToolBar->addAction(saveAllAction);
    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAction = new QAction(exitIcon, QStringLiteral("退出&(X)"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(exitAction);
    //File Menu End

#ifndef QT_NO_CLIPBOARD
    //Edit Menu Start
    QMenu *editMenu = menuBar()->addMenu(QStringLiteral("编辑&(E)"));
    QToolBar *editToolBar = addToolBar(QStringLiteral("编辑"));

    const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon("./images/undo.png"));
    QAction *undoAction = new QAction(undoIcon, QStringLiteral("撤销&(Z)"), this);
    undoAction->setShortcuts(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::slot_Undo);
    editMenu->addAction(undoAction);
    editToolBar->addAction(undoAction);

    const QIcon redoIcon = QIcon::fromTheme("edit-redo", QIcon("./images/redo.png"));
    QAction *redoAction = new QAction(redoIcon, QStringLiteral("恢复&(Y)"), this);
    redoAction->setShortcuts(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::slot_Redo);
    editMenu->addAction(redoAction);
    editToolBar->addAction(redoAction);
    editMenu->addSeparator();

    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon("./images/cut.png"));
    QAction *cutAction = new QAction(cutIcon, QStringLiteral("剪切"), this);
    cutAction->setShortcuts(QKeySequence::Cut);
    connect(cutAction, &QAction::triggered, this, &MainWindow::slot_Cut);
    editMenu->addAction(cutAction);
    editToolBar->addAction(cutAction);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon("./images/copy.png"));
    QAction *copyAction = new QAction(copyIcon, QStringLiteral("复制"), this);
    copyAction->setShortcuts(QKeySequence::Copy);
    connect(copyAction, &QAction::triggered, this, &MainWindow::slot_Copy);
    editMenu->addAction(copyAction);
    editToolBar->addAction(copyAction);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon("./images/paste.png"));
    QAction *pasteAction = new QAction(pasteIcon, QStringLiteral("粘贴"), this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::slot_Paste);
    editMenu->addAction(pasteAction);
    editToolBar->addAction(pasteAction);
    //Edit Menu End
#endif
    //Windows Menu Start
    windowsMenu = menuBar()->addMenu(QStringLiteral("窗口&(W)"));
    connect(windowsMenu, &QMenu::aboutToShow, this, &MainWindow::slot_updateWindowsMenu);

    closeAction = new QAction(QStringLiteral("关闭"), this);
    //connect(closeAction, &QAction::triggered, ui->mdiArea, &QMdiArea::closeActiveSubWindow);

    closeAllAction = new QAction(QStringLiteral("关闭所有"), this);
   // connect(closeAllAction, &QAction::triggered, ui->mdiArea, &QMdiArea::closeAllSubWindows);

    tileAction = new QAction(QStringLiteral("平铺"), this);
    //connect(tileAction, &QAction::triggered, ui->mdiArea, &QMdiArea::tileSubWindows);

    cascadeAction = new QAction(QStringLiteral("重叠"), this);
    //connect(cascadeAction, &QAction::triggered, ui->mdiArea, &QMdiArea::cascadeSubWindows);

    nextAction = new QAction(QStringLiteral("下一个"), this);
    nextAction->setShortcuts(QKeySequence::NextChild);
    //connect(nextAction, &QAction::triggered, ui->mdiArea, &QMdiArea::activateNextSubWindow);

    previousAction = new QAction(QStringLiteral("上一个"), this);
    previousAction->setShortcuts(QKeySequence::PreviousChild);
    //connect(previousAction, &QAction::triggered, ui->mdiArea, &QMdiArea::activatePreviousSubWindow);

    windowMenuSeparatorAction = new QAction(this);
    windowMenuSeparatorAction->setSeparator(true);
    slot_updateWindowsMenu();
    menuBar()->addSeparator();
    //Windows Menu End

    //View Menu Start
    QMenu *ViewMenu = menuBar()->addMenu(QStringLiteral("视图&(V)"));

    QAction *atnLibraryAction = antLibraryDock->toggleViewAction();
    //atnLibraryAction->setShortcut(QKeySequence("Ctrl+H"));
    ViewMenu->addAction(atnLibraryAction);

    QAction *proTreeAction = proTreeDock->toggleViewAction();
    ViewMenu->addAction(proTreeAction);

    QAction *stateAction = stateDock->toggleViewAction();
    ViewMenu->addAction(stateAction);

    QAction *printAction = printDock->toggleViewAction();
    ViewMenu->addAction(printAction);
    //View Menu End

    //Help Menu Start
    QMenu *helpMenu = menuBar()->addMenu(QStringLiteral("帮助&(H)"));

    QAction *aboutAction = new QAction(QStringLiteral("关于"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::slot_About);
    helpMenu->addAction(aboutAction);

    QAction *aboutQtAction = new QAction(QStringLiteral("关于Qt"), this);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    helpMenu->addAction(aboutQtAction);
    //Help Menu End

    //execution
    QToolBar *execToolBar = addToolBar(QStringLiteral("执行"));
    const QIcon stopAtnIcon = QIcon::fromTheme("find-atenna", QIcon("./images/stop.png"));
    QAction *stopAtnAction = new QAction(stopAtnIcon, QStringLiteral("终止"), this);
    execToolBar->addAction(stopAtnAction);

    const QIcon runAtnIcon = QIcon::fromTheme("find-atenna", QIcon("./images/run.png"));
    QAction *runAtnAction = new QAction(runAtnIcon, QStringLiteral("运行"), this);
    execToolBar->addAction(runAtnAction);

    const QIcon interruptAtnIcon = QIcon::fromTheme("find-atenna", QIcon("./images/interrupt.png"));
    QAction *interruptAtnAction = new QAction(interruptAtnIcon, QStringLiteral("中断"), this);
    execToolBar->addAction(interruptAtnAction);

    /*const QIcon findAtnIcon = QIcon::fromTheme("find-atenna", QIcon("./images/search.png"));
    QAction *findAtnAction = new QAction(findAtnIcon, QStringLiteral("查找"), this);
    //connect(findAtnAction, &QAction::triggered, this, &MainWindow::findAtn);
    execToolBar->addAction(findAtnAction);*/

    //other
    QToolBar *otherToolBar = addToolBar(QStringLiteral("其他"));
    searchAct = new searchAction(this);
    otherToolBar->addAction(searchAct);
}

void MainWindow::slot_NewProject(){
    projectWizard* wizard = new projectWizard(NULL, this);
    wizard->setAttribute(Qt::WA_DeleteOnClose);
    if(wizard->exec() == 1){
        //mTreeModel->showTree();
    }
}

void MainWindow::slot_OpenProject(){
    QString defaultDir = sysParam["DefaultProjectPath"];
    if(defaultDir.isNull() || defaultDir.isEmpty())
        defaultDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString path = QFileDialog::getOpenFileName(this, tr("打开工程"), defaultDir, tr("REL Files(*.rel)"));
    if(path.length() == 0){
        //QMessageBox::critical(0, QString("Error"), QString("MainWindow.cpp:242: error: rel文件打开失败"));
        qDebug() << "MainWindow.cpp:242: error: rel文件打开失败";
        //QMessageBox::warning(0, "警告！", "MainWindow.cpp:242: error: rel文件打开失败", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    mTreeModel->parseXML(QString("%1.xml").arg(path.split(".").at(0)));
    sysParam["WorkingProjectPath"] = QFileInfo(path).absolutePath();
    qDebug() << "OpenProject:WorkingProjectPath=" << sysParam["WorkingProjectPath"];
    //QMessageBox::information(this, "infomation", "test my openAction");
}
void MainWindow::slot_Save(){}
void MainWindow::slot_SaveAs(){}
void MainWindow::slot_SaveAll(){}
void MainWindow::slot_Undo(){}
void MainWindow::slot_Redo(){}
void MainWindow::slot_Cut(){}
void MainWindow::slot_Copy(){}
void MainWindow::slot_Paste(){}
void MainWindow::slot_About(){}
void MainWindow::slot_updateWindowsMenu(){
    windowsMenu->clear();
    windowsMenu->addAction(closeAction);
    windowsMenu->addAction(closeAllAction);
    windowsMenu->addSeparator();
    windowsMenu->addAction(tileAction);
    windowsMenu->addAction(cascadeAction);
    windowsMenu->addSeparator();
    windowsMenu->addAction(nextAction);
    windowsMenu->addAction(previousAction);
    windowsMenu->addAction(windowMenuSeparatorAction);

    /*QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    windowMenuSeparatorAction->setVisible(!windows.isEmpty());
    for (int i = 0; i < windows.size(); ++i) {
        QMdiSubWindow *mdiSubWindow = windows.at(i);
        MdiChild *child = qobject_cast<MdiChild *>(mdiSubWindow->widget());
        QString text;
        if (i < 9) {
            text = QStringLiteral("&%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
        } else {
            text = QStringLiteral("%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
        }
        QAction *action = windowsMenu->addAction(text, mdiSubWindow, ActiveMdiSubWindowFunctor(ui->mdiArea, mdiSubWindow));
        action->setCheckable(true);
        action->setChecked(child == activeMdiChild());
    }*/
}

/*MdiChild* MainWindow::activeMdiChild(){
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}*/

void MainWindow::slot_showProTree(bool isShow){
    if(isShow == true)
        qDebug() << true;
        //mTreeModel->showTree();
}

void MainWindow::slot_getClsoeSubmdiFlag(bool isClose){
    isClosedSubmdi = isClose;
}

void MainWindow::slot_clickSearchButton(){}
void MainWindow::slot_searchTextChange(QString searchText){

    searchDock->setWidget(searchAtnTable->getLabel());
    if (searchText == NULL){
        searchDock->hide();
        antLibraryDock->raise();
    }
    else{
        //sqliteManage* mSqlManage = new sqliteManage();
        QString sql = QString("select pModelPath, pName from antennaProblem where pName like '%%1%' or pInfo like '%%1%';").arg(searchText);
        QSqlQuery sqlQuery;
        sqlQuery.prepare(sql);
        QList<antennaCell* >atnCellList;
        if(!sqlQuery.exec(sql)){
            qDebug()<< sqlQuery.lastError();
        }
        else{
            while(sqlQuery.next()){
                antennaCell* atnCellTemp = new antennaCell(sqlQuery.value("pModelPath").toString(), sqlQuery.value("pName").toString());
                atnCellList.append(atnCellTemp);
            }
        }
        if (atnCellList.size() != 0){
            searchDock->setWidget(searchAtnTable->getTableWidget());
            searchAtnTable->arrangeAtn(atnCellList);
        }
        searchDock->show();
        searchDock->raise();
        //delete mSqlManage;
    }
}

// set dock size(default wh = -1, ht = -1)
void MainWindow::setDockSize(QDockWidget *dock, int wh, int ht){
    if(wh > 0){
        int dockWH = dock->width();
        if(dockWH < wh){
            dock->setMinimumWidth(wh);
        }
        else{
            dock->setMaximumWidth(wh);
        }
    }
    if(ht > 0){
        int dockHT = dock->height();
        if(dockHT < ht){
            dock->setMinimumHeight(ht);
        }
        else{
            dock->setMaximumHeight(ht);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
