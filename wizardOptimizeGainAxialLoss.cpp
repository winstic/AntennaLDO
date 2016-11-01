#include "wizardOptimizeGainAxialLoss.h"

wizardOptimizeAXL::wizardOptimizeAXL(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    setTitle(tr("增益轴比回波损失设置"));
    setSubTitle(tr("设置增益轴比回波损失等参数"));
    this->obj = obj;
    this->groupBoxGain = new QGroupBox(tr("增益设置"));
    this->groupBoxAxial = new QGroupBox(tr("轴比设置"));
    this->groupBoxLoss = new QGroupBox(tr("回波损失"));
    this->gainTable = new QTableWidget();
    this->axialTable = new QTableWidget();
    this->lossTable = new QTableWidget();

    gainSetting();
    axialSetting();
    lossSetting();
    initLayout();
}

bool wizardOptimizeAXL::gainSetting(){
    QStringList header;
    header << "起始θ" << "终止θ" << "起始φ" << "终止φ" << "优化方式" << "误差值" << "增益(dB)" << "权值";
    gainTable->setHorizontalHeaderLabels(header);
    gainTable->verticalHeader()->setHidden(true);       //hide column header number
    return true;

}

bool wizardOptimizeAXL::axialSetting(){
    QStringList header;
    header << "起始θ" << "终止θ" << "起始φ" << "终止φ" << "优化方式" << "误差值" << "轴比(dB)" << "权值";
    axialTable->setHorizontalHeaderLabels(header);
    axialTable->verticalHeader()->setHidden(true);       //hide column header number
    return true;
}

bool wizardOptimizeAXL::lossSetting(){
    QStringList header;
    header << "Z0实部" << "Z0虚部" << "损失方式" << "优化方式" << "误差实部" << "误差虚部" << "值实部" << "值虚部" << "权值";
    lossTable->setHorizontalHeaderLabels(header);
    lossTable->verticalHeader()->setHidden(true);       //hide column header number
    return true;
}

void wizardOptimizeAXL::initLayout(){
    QHBoxLayout *gainLayout = new QHBoxLayout;
    gainLayout->addWidget(gainTable);
    groupBoxGain->setLayout(gainLayout);

    QHBoxLayout *axialLayout = new QHBoxLayout;
    axialLayout->addWidget(axialTable);
    groupBoxAxial->setLayout(axialLayout);

    QHBoxLayout *lossLayout = new QHBoxLayout;
    lossLayout->addWidget(lossTable);
    groupBoxLoss->setLayout(lossLayout);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(groupBoxGain);
    vlayout->addWidget(groupBoxAxial);
    vlayout->addWidget(groupBoxLoss);
    vlayout->setSpacing(30);
    vlayout->setContentsMargins(2,20,2,2);
    setLayout(vlayout);
}

bool wizardOptimizeAXL::validatePage(){
    return true;
}
