#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QTextStream>
#include <QtWidgets>

class config{
public:
    config(){
        fileName = "./Config.ini";
    }
    ~config(){}
    void writeConfigInfo(const QString &key, const QString &value){
        QFile outfile(fileName);
        if (!outfile.open(QFile::Text | QFile::ReadOnly)){
            QMessageBox::warning(new QWidget, "警告！", "Config.ini文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
        QTextStream txtOutput(&outfile);
        QString str = txtOutput.readAll();
        outfile.close();

        if (!outfile.open(QFile::Text | QFile::WriteOnly)){
            QMessageBox::warning(new QWidget, "警告！", "Config.ini文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
        QTextStream out(&outfile);

        bool isWriten = false;
        QStringList strList = str.split("\n", QString::SkipEmptyParts);
        for(int i = 0; i < strList.count(); ++ i){
            if(strList.at(i).contains(key)){
                QString tempStr = strList.at(i);
                tempStr.replace(0, tempStr.length(), QString("%1 = %2").arg(key).arg(value));
                out << tempStr << "\n";
                isWriten = true;
            }
            else{
                out << strList.at(i) << "\n";
            }
        }
        if(!isWriten)
            out << QString("%1 = %2\n").arg(key).arg(value);
        outfile.close();
    }
    QString readPath(const QString &key){
        QFile infile(fileName);
        if (!infile.open(QFile::Text|QFile::ReadOnly)){
            QMessageBox::warning(new QWidget, "警告！", "Config.ini文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return NULL;
        }
        QTextStream txtInput(&infile);
        QString str = txtInput.readAll();
        infile.close();

        QStringList strList = str.split("\n", QString::SkipEmptyParts);
        for(int i = 0 ; i < strList.count(); ++ i){
            if(strList.at(i).contains(key)){
                QStringList tempList = QString(strList.at(i)).split("=");
                return tempList.at(1).trimmed();
            }
        }

        return NULL;
    }
private:
    QString fileName;
};

#endif // CONFIG_H
