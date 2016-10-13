#include "projectWizard.h"
#include "global.h"

projectWizard::projectWizard(QString antennaName, QWidget *parent) : QWizard(parent){
    atnName = antennaName;
    setWindowTitle(atnName + " 工程向导");
    setButtonText(QWizard::NextButton, "下一步>");
    introduce = new wizardIntroduce(atnName, this);
    addSetting = new wizardAddSetting(atnName, this);
    // need improve
    selectPy = new wizardSelectPy(atnName);
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

    //create project dir
	QDir *dir = new QDir();
    dir->mkdir(projectFullPath);

    //copy antenna problem
    QString projectProPath = QString("%1/%2_conf.json").arg(projectFullPath).arg(atnName);
    QString projectModelPath = QString("%1/%2.hfss").arg(projectFullPath).arg(atnName);
    QString projectScriptPath = QString("%1/%2_design.vbs").arg(projectFullPath).arg(atnName);
    if(! global::copyFile(QString("%1/%2_conf.json").arg(proPath).arg(atnName), projectProPath) ||
           ! global::copyFile(QString("%1/%2.hfss").arg(proPath).arg(atnName), projectModelPath) ||
            ! global::copyFile(QString("%1/%2_design.vbs").arg(proPath).arg(atnName), projectScriptPath) ){
        QMessageBox::critical(0, QString("Error"), QString("projectWizard.cpp:79: error: 问题文件创建失败！"));
        dir->rmdir(projectFullPath);
        return;
    }

    //confManage->writeConfigInfo("MODELVARIABLES", projectProPath);
    //confManage->writeConfigInfo("MODELFILE", projectModelPath);
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
    //out << projectAlgPath << endl;
    inFile.close();
}

QString projectWizard::getProjectName() const{
    return projectName;
}
