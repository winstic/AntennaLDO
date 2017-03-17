#include "../Global/global.h"
#include "projectWizard.h"


projectWizard::projectWizard(QString antennaName, QWidget *parent) : QWizard(parent){
    atnName = antennaName;
    setWindowTitle(atnName + " 工程向导");
    //remove help menu
    this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    setButtonText(QWizard::NextButton, "下一步>");
    introduce = new wizardIntroduce(atnName);
    addSetting = new wizardAddSetting(atnName);
    selectPy = new wizardSelectPy(atnName);
    // need improve

    //confManage = new config();

    if (atnName != NULL){
        addPage(introduce);
        addPage(addSetting);        
    }
    else{
        addPage(addSetting);
        addPage(selectPy);
    }
    this->setMinimumSize(880, 580);
}

bool projectWizard::validateCurrentPage(){
    if (this->currentPage()->nextId() == -1){
            bool finish = addSetting->validatePage();            
            if (finish==true){
                //addSetting->writeDefaultPath();
                //in this function init some private paramters
                createProject();
                if(addSetting->isSettingDefaultPath())
                    sysParam["DefaultProjectPath"] = projectPath;
                    //confManage->writeConfigInfo("DefaultProjectPath", projectPath);
                else
                    sysParam["DefaultProjectPath"] = "";
                    //confManage->writeConfigInfo("DefaultProjectPath", "");
                sysParam["WorkingProjectPath"] = projectFullPath;
                //confManage->writeConfigInfo("WORKINGPATH", projectPath);
                qDebug() << "DefaultProjectPath=" << sysParam["DefaultProjectPath"];
                qDebug() << "projectWizard:WorkingProjectPath=" << sysParam["WorkingProjectPath"];
            }
            return finish;
        }
    /*if (this->currentPage()->nextId() == -1){
        bool finish = selectPy->validatePage();
        if (finish==true && addSetting->isSettingDefaultPath())
            addSetting->writeDefaultPath();
        if (finish == true){
			createProject();
		}
        return selectPy->validatePage();
    }
	if (this->currentPage()->nextId() == 2)	{
        return addSetting->validatePage();
    }*/
	return true;
}

void projectWizard::createProject(){
    this->projectName = addSetting->getProjectName();
    this->projectPath = addSetting->getProjectPath();
    this->projectFullPath = projectPath + "/" + projectName;
    QString proPath = selectPy->getProPath();
    QString algPath= selectPy->getAlgPath();
    QString relFile = projectName + ".rel";
    bool isSuccess = false;

    //create project dir
	QDir *dir = new QDir();
    dir->mkdir(projectFullPath);

    //copy antenna problem
    QString projectProPath = QString("%1/%2_conf.json").arg(projectFullPath).arg(atnName);
    QString projectModelPathHfss = QString("%1/%2.hfss").arg(projectFullPath).arg(atnName);
    QString projectModelPathFeko = QString("%1/%2.cfx").arg(projectFullPath).arg(atnName);
    QString projectScriptPath = QString("%1/%2_design.vbs").arg(projectFullPath).arg(atnName);

    //后续在数据库中添加问题标识来区别问题（hfss/feko/...）
    proType atntype = hfss;
    if(global::copyFile(QString("%1/%2_conf.json").arg(proPath).arg(atnName), projectProPath)){
        //hfss problem
        if(global::copyFile(QString("%1/%2.hfss").arg(proPath).arg(atnName), projectModelPathHfss) &&
                global::copyFile(QString("%1/%2_design.vbs").arg(proPath).arg(atnName), projectScriptPath)){
            atntype = hfss;
            isSuccess = true;
        }

        //feko problem
        if( global::copyFile(QString("%1/%2.cfx").arg(proPath).arg(atnName), projectModelPathFeko) ){
            atntype = feko;
            isSuccess = true;
        }
    }

    if(!isSuccess){
        QMessageBox::critical(0, QString("Error"), QString("projectWizard.cpp:97: error: 问题文件创建失败！"));
        dir->rmdir(projectFullPath);
        return;
    }

    //confManage->writeConfigInfo("MODELVARIABLES", projectProPath);
    //confManage->writeConfigInfo("MODELFILE", projectModelPathHfss);
    //copy algorithm
    /*QString projectAlgPath = projectFullPath + "/" + QFileInfo(algPath).fileName();
    if(! global::copyFile(algPath, projectAlgPath)){
        QMessageBox::warning(this, "警告！", "算法文件创建失败！", QMessageBox::Yes, QMessageBox::Yes);
        dir->remove(projectFullPath);
        return;
    }*/

    //writen project file(.rel)
    QFile inFile(projectFullPath + "/" + relFile);
    inFile.open(QIODevice::WriteOnly);
    QTextStream out(&inFile);
    out << "Problem:" << atnName << endl;
    out << "ProType:" << atntype << endl;
    //out << projectAlgPath << endl;
    inFile.close();
}

QString projectWizard::getProjectName() const{
    return projectName;
}
