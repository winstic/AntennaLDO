#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QMap>
#include <QFileInfo>
#include <QDir>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>

extern QMap<QString, QString> sysParam;
//! sysParam["DefaultProjectPath"]
//! sysParam["WorkingProjectPath"]
//! sysParam["CurrentDesignPath"]
//! sysParam["CurrentOptimizePath"]

typedef struct{
    double lower;
    double upper;
    QString varKey;
    QSlider *varSlider;
    QLineEdit *varEdit;
    //QComboBox *varComboBox;
}varInfo;

class global{
public:
    global();
    ~global(){}
    static QStringList str2list(QString str);
    static QString str2liststr(const QString &str);
    static QString getFileBySuffix(const QString &dir, const QString &suff);
    static void registerParamter();
    static QString getInfoFromRel(const QString &key);
    //static bool addedInfoInRel(const QString &key, const QString &value);
    static QString getProjectName();
    static bool copyFile(QString sourceFile, QString targetFile, bool coverFileIfExist = true);
public:
};

#endif // GLOBAL_H
