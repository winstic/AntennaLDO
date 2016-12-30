#include "wizardOptimizeAlg.h"

wizardOptimizeAlg::wizardOptimizeAlg(QWidget *parent) : QWizardPage(parent){
    setTitle(tr("优化算法设置"));
    setSubTitle(tr("设置算法参数"));
    this->atnName = global::getInfoFromRel("Problem");
    this->algLabel = new QLabel(tr("选择算法:"));
    this->generationLabel = new QLabel(tr("最大代数"));
    this->popsizeLabel = new QLabel(tr("种群规模"));
    this->threadLabel = new QLabel(tr("启动进程数"));
    this->algCombo = new QComboBox();
    this->hint = new QLabel();
    this->generationLine = new QLineEdit();
    this->popsizeLine = new QLineEdit();
    this->threadLine = new QLineEdit();

    this->proPath = setPath(atnName, proPy);
    setAlgComboItem(atnName);
    algCombo->setCurrentIndex(0);
    this->algName = algCombo->currentText().trimmed();
    this->algPath = setPath(algName, algPy);

    //get thread num from global_conf.json
    QString DEA4ADglobalPath = QString("./DEA4AD/trunk");
    QString globalJsonPath = QString("%1/global_conf.json").arg(DEA4ADglobalPath);
    QJsonObject globalObj = parseJson::getJsonObj(globalJsonPath);
    threadLine->setText(QString::number(globalObj.value("ThreadNum").toString().trimmed().toInt()-1));

    confSetting();
    initLayout();
    connect(algCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_algName(int)));
}

void wizardOptimizeAlg::confSetting(){
    QString algConfJaonPath = QString("%1/%2_conf.json").arg(algPath).arg(algName);
    QJsonObject algObj = parseJson::getJsonObj(algConfJaonPath);
    generationLine->setText(algObj.value("generation").toString().trimmed());
    popsizeLine->setText(algObj.value("popsize").toString().trimmed());
}

void wizardOptimizeAlg::initLayout(){
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    //algorithm name
    algLabel->setFixedWidth(80);
    hlayout1->addWidget(algLabel);
    hlayout1->addWidget(algCombo);
    vlayout1->addLayout(hlayout1);

    QGroupBox *algGroup = new QGroupBox();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    //generation setting
    generationLabel->setFixedWidth(80);
    hlayout2->addWidget(generationLabel);
    hlayout2->addWidget(generationLine);
    vlayout2->addLayout(hlayout2);
    vlayout2->addSpacing(50);
    //popsize setting
    hlayout2 = new QHBoxLayout();
    popsizeLabel->setFixedWidth(80);
    hlayout2->addWidget(popsizeLabel);
    hlayout2->addWidget(popsizeLine);
    vlayout2->addLayout(hlayout2);
    vlayout2->addSpacing(50);
    //thread number
    hlayout2 = new QHBoxLayout();
    threadLabel->setFixedWidth(80);
    hlayout2->addWidget(threadLabel);
    hlayout2->addWidget(threadLine);
    vlayout2->addLayout(hlayout2);
    algGroup->setLayout(vlayout2);

    /*QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addLayout(vlayout1);
    hlayout->addSpacing(40);
    hlayout->addWidget(algGroup);*/
    //hint
    QHBoxLayout *hlayout3 = new QHBoxLayout();
    hint->setAlignment(Qt::AlignRight);
    hlayout3->addWidget(hint);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(vlayout1);
    vlayout->addSpacing(50);
    vlayout->addWidget(algGroup);
    vlayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlayout->addLayout(hlayout3);

    vlayout->setContentsMargins(20, 50, 20, 20);
    setLayout(vlayout);
}

void wizardOptimizeAlg::setAlgComboItem(QString name){
    QString selectProSql = QString(" select a.aId, a.aName "
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
        }
    }
}

QString wizardOptimizeAlg::setPath(QString name, bool flag){
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

QString wizardOptimizeAlg::getProPath() const{
    return proPath;
}

QString wizardOptimizeAlg::getAlgPath() const{
    return algPath;
}

QString wizardOptimizeAlg::getAlgName() const{
    return algName;
}

QJsonObject wizardOptimizeAlg::saveInJsonObj(){
    QJsonObject saveObj, globalObj, algObj;
    globalObj.insert("ThreadNum", QString::number(threadLine->text().trimmed().toInt()+1));
    globalObj.insert("ALGORITHM_NAME", algName);
    globalObj.insert("PROBLEM_NAME", atnName);
    algObj.insert("generation", generationLine->text().trimmed());
    algObj.insert("popsize", popsizeLine->text().trimmed());

    saveObj.insert("global", globalObj);
    saveObj.insert("algorithm", algObj);
    return saveObj;
}

bool wizardOptimizeAlg::validatePage(){
    if (algCombo->currentIndex() == -1){
        hint->setStyleSheet("font-color:red");
        hint->setText("请选择算法！");
        return false;
    }
    return true;
}

void wizardOptimizeAlg::slot_algName(const int index){
    algName = algCombo->itemText(index);
    algPath = setPath(algName, algPy);
    confSetting();
}
