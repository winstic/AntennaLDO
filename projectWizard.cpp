#include "projectWizard.h"

projectWizard::projectWizard(QString antennaName, QWidget *parent) : QWizard(parent){
    atnName = antennaName;
    setWindowTitle(atnName + " 工程向导");
    setButtonText(QWizard::NextButton, "下一步>");
    introduce = new wizardIntroduce(atnName, this);
    addSetting = new wizardAddSetting(atnName, this);
    // need improve
    selectPy = new wizardSelectPy(atnName);
    confManage = new config();

    if (atnName != NULL){
        addPage(introduce);
        addPage(addSetting);        
    }
    else{
        addPage(addSetting);
        addPage(selectPy);
    }
}

bool projectWizard::validateCurrentPage(){
    if (this->currentPage()->nextId() == -1){
            bool finish = addSetting->validatePage();            
            if (finish==true){
                //addSetting->writeDefaultPath();
                createProject();
                if(addSetting->isSettingDefaultPath())
                    confManage->writeConfigInfo("PROJECTPATH", projectPath);
                else
                    confManage->writeConfigInfo("PROJECTPATH", "");
                confManage->writeConfigInfo("WORKINGPATH", projectPath);
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
    if(! copyFile(QString("%1/%2_conf.json").arg(proPath).arg(atnName), projectProPath) ||
           ! copyFile(QString("%1/%2.hfss").arg(proPath).arg(atnName), projectModelPath) ){
        QMessageBox::warning(this, "警告！", "问题文件创建失败！", QMessageBox::Yes, QMessageBox::Yes);
        dir->rmdir(projectFullPath);
        return;
    }
    confManage->writeConfigInfo("MODELVARIABLES", projectProPath);
    confManage->writeConfigInfo("MODELFILE", projectModelPath);
    //copy algorithm
    /*QString projectAlgPath = projectFullPath + "/" + QFileInfo(algPath).fileName();
    if(! copyFile(algPath, projectAlgPath)){
        QMessageBox::warning(this, "警告！", "算法文件创建失败！", QMessageBox::Yes, QMessageBox::Yes);
        dir->remove(projectFullPath);
        return;
    }*/

    //writen project file(.rel)
    QFile inFile(projectFullPath + "/" + relFile);
    inFile.open(QIODevice::WriteOnly);
    QTextStream out(&inFile);
    out << projectProPath << endl;
    //out << projectAlgPath << endl;
    inFile.close();
}

bool projectWizard::copyFile(QString sourceFile, QString targetFile, bool coverFileIfExist){
    QString sourceDir = QDir(sourceFile).absolutePath();
    QString targetDir = QDir(targetFile).absolutePath();
    if(sourceDir == targetDir){
        return true;
    }
    if(! QFile::exists(sourceDir)){
        return false;
    }
    QDir* createFile = new QDir;
    bool isExist = createFile->exists(targetDir);
    if(isExist && coverFileIfExist){
        createFile->remove(targetDir);
    }
    //copy function: if targetDir already exist then return false
    if(! QFile::copy(sourceDir, targetDir)){
        return false;
    }
    return true;
}

QString projectWizard::getProjectName() const{
    return projectName;
}
