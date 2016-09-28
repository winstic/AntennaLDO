#ifndef ATNLIBRARY_H
#define ATNLIBRARY_H

#include <QListView>

#include "global.h"
#include "mybtn.h"
#include "sqliteManage.h"
#include "antennaCell.h"
#include "projectWizard.h"
#include "treeModel.h"

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

private:
    treeModel *mTreeModel;
    QTableWidget* tableView;
    QLabel* failedSearch;
    int atnDockWH;
    int numOfTableCol;

    void showInfo();
    QList<int> setAtnWidth(int width, int colNum);
};


#endif // ATNLIBRARY_H
