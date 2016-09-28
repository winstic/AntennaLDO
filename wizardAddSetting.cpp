#include "wizardAddSetting.h"

wizardAddSetting::wizardAddSetting(QString antennaName, QWidget *parent) : QWizardPage(parent){
	setTitle("基本设置");
    projectName_label = new QLabel("工程名称：");
    projectName_edit = new QLineEdit;
    projectPath_label = new QLabel("工程路径：");
    projectPath_edit = new QLineEdit;
    selectPath_btn = new QPushButton("浏览");
    alwaysPath = new QRadioButton("设为默认路径");
    hint = new QLabel("请输入工程名称。");

	QHBoxLayout *hlayout = new QHBoxLayout;
	QVBoxLayout *vlayout = new QVBoxLayout;
    hlayout->addWidget(projectName_label);
    hlayout->addWidget(projectName_edit);
	vlayout->addLayout(hlayout);
	hlayout = new QHBoxLayout;
    hlayout->addWidget(projectPath_label);
    hlayout->addWidget(projectPath_edit);
    hlayout->addWidget(selectPath_btn);
	
	
	vlayout->addLayout(hlayout);
    vlayout->addWidget(alwaysPath);

	hlayout = new QHBoxLayout;
	hlayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout->addWidget(hint);
	vlayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
	vlayout->addLayout(hlayout);
    setLayout(vlayout);

    alwaysPath->setChecked(true);
	//读取默认路径
    projectPath = readDefaultPath();
    projectPath_edit->setText(projectPath);
    projectPath_edit->setReadOnly(true);
    //registerField("projectName*", projectName_edit);
//	registerField("projectPath*", projectPath_edit);

    connect(selectPath_btn, SIGNAL(clicked()), this, SLOT(slot_selectPath()));
    connect(projectName_edit, SIGNAL(textChanged(QString)), this, SLOT(slot_giveHintName(QString)));
}

bool wizardAddSetting::validatePage(){
    projectName = projectName_edit->text();

	QRegExp reg(" *");
    if (reg.exactMatch(projectName)){
        projectName_edit->setFocus();
		return false;
	}

    if (projectPath == ""){
        hint->setText("无效的路径！");
		return false;
	}	
	QDir dir;
    if (dir.exists(projectPath + "/" + projectName)){
        hint->setText("当前目录已存在" + projectName);
		return false;
	}

	return true;
}

QString wizardAddSetting::readDefaultPath(){
    QFile infile("./System.set");
    if (!infile.open(QFile::Text|QFile::ReadOnly)){
		QMessageBox::warning(this, "警告！", "System.set文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return "";
	}
	QTextStream txtInput(&infile);
	QString str;
	str = txtInput.readAll();
	QStringList str_list = str.split("%");
	int index=str_list.indexOf("defaultProjectPath");
	infile.close();
	return str_list[index+1];
}

void wizardAddSetting::writeDefaultPath(QString path){
    QFile outfile("./System.set");
    if (!outfile.open(QFile::Text | QFile::ReadOnly)){
		QMessageBox::warning(this, "警告！", "System.set文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	QTextStream txtOutput(&outfile);
	QStringList str_list;
	QString str = txtOutput.readAll();
	str_list = str.split("%");
	outfile.close();
    if (!outfile.open(QFile::Text | QFile::WriteOnly)){
		QMessageBox::warning(this, "警告！", "System.set文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
    for (int i = 0; i < str_list.size(); i++){
		if (str_list[i] == "defaultProjectPath")
            str_list[i + 1] = projectPath;
		if (i != str_list.size() - 1)
			txtOutput << str_list[i] << "%";
		else
			txtOutput << str_list[i];
	}
}

bool wizardAddSetting::isSettingDefaultPath() const{
    return alwaysPath->isChecked();
}

QString wizardAddSetting::getProjectPath() const{
    return projectPath;
}

QString wizardAddSetting::getProjectName() const{
    return projectName;
}

// slots functions
void wizardAddSetting::slot_selectPath(){
    QFileDialog* openFilePath = new QFileDialog(this);
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString selectDir = openFilePath->getExistingDirectory(this, tr("选择文件夹"), homeDir,
                                                           QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    projectPath_edit->setText(selectDir);
    projectPath = projectPath_edit->text();
    alwaysPath->setChecked(false);
    if (projectPath == ""){
        hint->setText("请选择工程路径!");
    }
    else{
        hint->setText("工程将创建在该路径下。");
    }
}

void wizardAddSetting::slot_giveHintName(QString name){
    projectName = name;
	QRegExp reg(" *");
    if (reg.exactMatch(name)){
        hint->setText("工程名称不能为空！");
	}
    else{
        hint->setText("该工程名将是您的工程目录名。");
	}
}


 
