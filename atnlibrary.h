#ifndef ATNLIBRARY_H
#define ATNLIBRARY_H

#include <QListView>

#include "macrodefined.h"
#include "sqliteManage.h"
#include "antennaCell.h"
#include "projectWizard.h"
#include "treeModel.h"
#include "modelfile.h"
//#include "config.h"

class atnLibrary : public QWidget{
    Q_OBJECT
public:
    atnLibrary(QString sql, treeModel *mTreeModel, QWidget *parent = 0);
    ~atnLibrary(){}

    QTableWidget* getTableWidget() const;
    QLabel* getLabel() const;
    void arrangeAtn(QList<antennaCell *> atnList, int tabWH = 1152, int numOfCol = 6);

    QList<antennaCell *> setAtnList(QString selectSql);
    int getAtnDockWH();
    /*QSize sizeHint() const{
        return QSize(500, 900);
    }*/

signals:
    void signal_sendShowPro(bool);

public slots:
    void slot_reSizeSlot(int row, int column);
    //是否显示工程结构
    void slot_showProTree(bool isShow);
    void slot_tableCellDoubleClick(int, int);
    void slot_customContextMenuRequested(QPoint);
    //emitted when the mouse button press
    void slot_cellPressed(int, int);
    void slot_property();
    void slot_newProject();

private:    
    void showInfo();
    QList<int> setAtnWidth(int width, int colNum);
    void initMenu();

    QString atnName;
    treeModel *mTreeModel;
    QTableWidget* tableView;
    QLabel* failedSearch;
    int atnDockWH;
    int numOfTableCol;
    QMenu *itemMenu;
    QAction *actNew;
    QAction *actProperty;
};


#endif // ATNLIBRARY_H
