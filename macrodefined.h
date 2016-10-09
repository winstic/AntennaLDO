#ifndef MACRODEFINED_H
#define MACRODEFINED_H

#define MBNTICON_WH 120
#define MBNTICON_HT 100
#define TOOLBNTSIZE 150
#define MBNTDIS 15
#define NUMOFANTENNA 60
#define CELLATNWH 182
#define CELLATNHT 140

// 工程树右键菜单role设定
#define ROLE_MARK Qt::UserRole + 1          //用于区分根节点、文件夹节点、条目节点的角色
#define ROLE_MARK_NODE Qt::UserRole + 2   //用于区分优化设计文件夹、结果文件夹的角色
#define ROLE_MARK_ITEM Qt::UserRole + 3     //用于区分所有条目节点

// 对应于ROLE_MARK，设定每种role的值
#define MARK_PROJECT 1
#define MARK_NODE 2
#define MARK_ITEM 3

// 对应于ROLE_MARK_FOLDER，设定每种role的值
#define MARK_NODE_GENERAL 1  //通用值（保留）
#define MARK_NODE_DESIGN 2
#define MARK_NODE_OPTIMIZATION 3
#define MARK_NODE_RESULT 4


//对应于ROLE_MARK_ITEM，设定每种角色的值
#define MARK_ITEM_OPENFILE 1
#define MARK_ITEM_PERDESIGN 2
#define MARK_ITEM_ALGDESIGN 3
#define MARK_ITEM_ATNDESIGN 4

enum pyFlag{proPy = 0, algPy};
enum SWEEPTYPES{linearly = 0, logarithmically};

#endif // MACRODEFINED_H
