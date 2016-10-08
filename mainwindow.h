#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "macrodefined.h"
#include "atnlibrary.h"
#include "treeModel.h"
#include "searchAction.h"
#include "wizardAddSetting.h"
#include "projectWizard.h"
#include "xmldomdocument.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init_Icon();
    void init_proTree();

    void createActions();
    //MdiChild* activeMdiChild();
    //子窗口
private slots:
    void slot_NewProject();
    void slot_OpenProject();
    void slot_Save();
    void slot_SaveAs();
    void slot_SaveAll();
#ifndef QT_NO_CLIPBOARD
    void slot_Undo();
    void slot_Redo();
    void slot_Cut();
    void slot_Copy();
    void slot_Paste();
#endif
    void slot_About();
    void slot_updateWindowsMenu();

    // 连接myBtn信号
    void slot_showProTree(bool isShow);
    void slot_getClsoeSubmdiFlag(bool isClose);
    //search antenna
    void slot_clickSearchButton();
    void slot_searchTextChange(QString);

private:
    Ui::MainWindow *ui;
    bool isClosedSubmdi;
    treeModel *mTreeModel;
    QMenu *windowsMenu;
    QAction *closeAction;
    QAction *closeAllAction;
    QAction *tileAction;
    QAction *cascadeAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *windowMenuSeparatorAction;
    QTreeView *proTree;
    searchAction *searchAct;
    atnLibrary* searchAtnTable;

    //dockwidget paremeters
    QDockWidget *stateDock;
    QDockWidget *printDock;
    QDockWidget *proTreeDock;
    QDockWidget *searchDock;
    QDockWidget *antLibraryDock;

    void init_docks();
    void layoutDock();
    void setDockSize(QDockWidget *dock, int wh = -1, int ht = -1);
};

#endif // MAINWINDOW_H
