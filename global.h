#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtWidgets>
#include <QIcon>
#include <QString>
#include <QMap>
#include <QAction>
#include <vector>

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

inline QStringList singleListRegularStr(QString str){
    QRegExp re("[\\[,\\]]");
    QStringList strList = str.split(re, QString::SkipEmptyParts);
    return strList;
}

//enum POLARIZATION{total = 0, left, right, horizontal, vertical};

//typedef  QMap<QString, QIcon> IconMap;

/*struct freVariables{
    vector<double> freStart;
    vector<double> freEnd;
    vector<int> freNumber;
    vector<SWEEPTYPES> sweepType;
    vector<POLARIZATION> PM;
};*/

//typedef QMap<QString, QVariant> modelVariables;

//UTF-8转Unicode
/*
std::wstring Utf82Unicode(const QString& utf8string){
    int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION){
        throw QString("Invalid UTF-8 sequence.");
    }
    if (widesize == 0){
        throw QString("Error in conversion.");
    }

    std::vector<wchar_t> resultstring(widesize);

    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

    if (convresult != widesize){
        throw QString("La falla!");
    }

    return std::wstring(&resultstring[0]);
}

//unicode 转为 ascii

QString WideByte2Acsi(std::wstring& wstrcode){
    int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION){
        throw QString("Invalid UTF-8 sequence.");
    }
    if (asciisize == 0){
        throw QString("Error in conversion.");
    }
    std::vector<char> resultstring(asciisize);
    int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

    if (convresult != asciisize){
        throw QString("La falla!");
    }

    return QString(&resultstring[0]);
}

//utf-8 转 ascii

QString UTF_82ASCII(QString& strUtf8Code){
    QString strRet("");

    //先把 utf8 转为 unicode
    std::wstring wstr = Utf82Unicode(strUtf8Code);

    //最后把 unicode 转为 ascii
    strRet = WideByte2Acsi(wstr);

    return strRet;
}

///////////////////////////////////////////////////////////////////////

//ascii 转 Unicode

std::wstring Acsi2WideByte(QString& strascii)
{
    int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION){
        throw QString("Invalid UTF-8 sequence.");
    }
    if (widesize == 0){
        throw QString("Error in conversion.");
    }
    std::vector<wchar_t> resultstring(widesize);
    int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);

    if (convresult != widesize){
        throw QString("La falla!");
    }

    return std::wstring(&resultstring[0]);
}

//Unicode 转 Utf8

QString Unicode2Utf8(const std::wstring& widestring)
{
    int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8size == 0){
        throw QString("Error in conversion.");
    }

    std::vector<char> resultstring(utf8size);

    int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);

    if (convresult != utf8size){
        throw QString("La falla!");
    }
    return QString(&resultstring[0]);
}

//ascii 转 Utf8

QString ASCII2UTF_8(QString& strAsciiCode)
{
    QString strRet("");

    //先把 ascii 转为 unicode
    std::wstring wstr = Acsi2WideByte(strAsciiCode);

    //最后把 unicode 转为 utf8
    strRet = Unicode2Utf8(wstr);

    return strRet;
}*/

#endif // GLOBAL_H
