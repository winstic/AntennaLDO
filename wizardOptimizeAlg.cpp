#include "wizardOptimizeAlg.h"

wizardOptimizeAlg::wizardOptimizeAlg(QWidget *parent) : QWizardPage(parent){
    setTitle(tr("优化算法设置"));
    setSubTitle(tr("设置算法参数"));
    this->atnName = global::getInfoFromRel("Problem");
    this->proLabel = new QLabel(tr("选择问题:"));
    this->algLabel = new QLabel(tr("选择算法:"));
    this->atnLine = new QLineEdit(atnName);
    atnLine->setReadOnly(true);
    this->algCombo = new QComboBox;
    this->hint = new QLabel;

    setAlgComboItem(atnName);
    algCombo->setCurrentIndex(0);
    initLayout();
}

void wizardOptimizeAlg::initLayout(){
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;
    proLabel->setFixedWidth(80);
    hlayout->addWidget(proLabel);
    hlayout->addWidget(atnLine);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(100);

    hlayout = new QHBoxLayout;
    algLabel->setFixedWidth(80);
    hlayout->addWidget(algLabel);
    hlayout->addWidget(algCombo);
    vlayout->addLayout(hlayout);

    hlayout = new QHBoxLayout;
    hint->setAlignment(Qt::AlignRight);
    hlayout->addWidget(hint);
    vlayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlayout->addLayout(hlayout);
    vlayout->setContentsMargins(20, 80, 20, 20);
    setLayout(vlayout);
}

void wizardOptimizeAlg::setAlgComboItem(QString name){
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

QJsonObject wizardOptimizeAlg::saveInJsonObj(){

}

bool wizardOptimizeAlg::validatePage(){
    if (algCombo->currentIndex() == -1){
        hint->setStyleSheet("font-color:red");
        hint->setText("请选择算法！");
        return false;
    }
    return true;
}
