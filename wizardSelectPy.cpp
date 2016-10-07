#include"wizardSelectPy.h"

wizardSelectPy::wizardSelectPy(QString antennaName, QWidget *parent) : QWizardPage(parent){
    atnName = antennaName;
    proLabel = new QLabel();
    proLabel->setText("选择问题:");
    algLabel = new QLabel;
    algLabel->setText("选择算法:");
    proCombo = new QComboBox;
    algCombo = new QComboBox;
    hint = new QLabel;
	QHBoxLayout *hbox=new QHBoxLayout;
	QVBoxLayout *vbox=new QVBoxLayout;

    hbox->addWidget(proLabel);
    hbox->addWidget(proCombo);
	hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
	vbox->addLayout(hbox);
	hbox = new QHBoxLayout;
    hbox->addWidget(algLabel);
    hbox->addWidget(algCombo);
	hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
	vbox->addLayout(hbox);
	vbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
	hbox = new QHBoxLayout;
	hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    hbox->addWidget(hint);
	vbox->addLayout(hbox);
	setLayout(vbox);

    initProCombo();
    if (atnName != NULL){
        proCombo->setCurrentIndex(proCombo->findText(atnName));
        proCombo->setEnabled(false);
        setAlgComBoItem(atnName);
        //proPath = setPath(atnName, proPy);
	}
    else{
        proCombo->setCurrentIndex(-1);
    }
    algCombo->setCurrentIndex(-1);

    connect(algCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_algName(int)));
    connect(proCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_proName(int)));
}

bool wizardSelectPy::validatePage(){
    if (proCombo->currentIndex() == -1){
        hint->setText("请选择天线问题！");
		return false;
	}
    if (algCombo->currentIndex() == -1){
        hint->setText("请选择算法！");
		return false;
	}
	return true;
}

void wizardSelectPy::initProCombo(){
    QString selectProSql = "select pName from antennaProblem;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(selectProSql);
    if(!sqlQuery.exec(selectProSql)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            proCombo->addItem(sqlQuery.value("pName").toString());
        }
    }
}

//flag==0 means return problem pyPath, flag==1 means return algorithm pyPath
QString wizardSelectPy::setPath(QString name, bool flag){
    QString pyPath;
    QString getPySql;
    QString pyFlag;
    if(flag == 0){
        getPySql = QString("select proPath from antennaProblem where pName = '%1';").arg(name);
        pyFlag = "proPath";
    }
    else{
        getPySql = QString("select algPath from algorithm where aName = '%1';").arg(name);
        pyFlag = "algPath";
    }
    QSqlQuery sqlQuery;
    sqlQuery.prepare(getPySql);
    if(!sqlQuery.exec(getPySql)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            pyPath = sqlQuery.value(pyFlag).toString();
        }
    }
    return pyPath;
}

void wizardSelectPy::setAlgComBoItem(QString name){
    QString selectProSql = QString(" select a.aId, a.aName, c.proPath "
            " from algorithm as a "
            " inner join algtopro as b on a.aId = b.aId and b.pId = c.pId "
            " inner join antennaProblem as c on c.pName = '%1'; ").arg(name);
    QSqlQuery sqlQuery;
    sqlQuery.prepare(selectProSql);
    if(!sqlQuery.exec(selectProSql)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            algCombo->addItem(sqlQuery.value("aName").toString());
            //resigned proPath many times need to improved
            proPath = sqlQuery.value("proPath").toString();
        }
    }
}

QString wizardSelectPy::getProPath() const{
    return proPath;
}

QString wizardSelectPy::getAlgPath() const{
    return algPath;
}

//slots function
void wizardSelectPy::slot_proName(int index){
    atnName = proCombo->itemText(index);
    setAlgComBoItem(atnName);
    hint->setText("所选问题为"+atnName);
}

void wizardSelectPy::slot_algName(int index){
    QString algName = algCombo->itemText(index);
    algPath = setPath(algName, algPy);
    hint->setText("所选算法为" + algName);
}


