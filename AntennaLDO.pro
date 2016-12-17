#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T20:51:08
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AntennaLDO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    designWizard.cpp \
    treeModel.cpp \
    wizardDesignPerformance.cpp \
    wizardAddSetting.cpp \
    wizardDesignVariables.cpp \
    atnlibrary.cpp \
    xmldomdocument.cpp \
    projectWizard.cpp \
    wizardIntroduce.cpp \
    wizardSelectPy.cpp \
    antennaCell.cpp \
    searchAction.cpp \
    sqliteManage.cpp \
    global.cpp \
    parsejson.cpp \
    designtab.cpp \
    modelfile.cpp \
    wizardOptimizeAlg.cpp \
    wizardOptimizeVariables.cpp \
    optimizeWizard.cpp \
    wizardOptimizeGainAxialLoss.cpp \
    optimizetab.cpp \
    designRun.cpp \
    optimizeRun.cpp

HEADERS  += mainwindow.h \
    wizardDesignPerformance.h \
    global.h \
    designWizard.h \
    treeModel.h \
    wizardDesignVariables.h \
    atnlibrary.h \
    projectWizard.h \
    xmldomdocument.h \
    wizardAddSetting.h \
    wizardIntroduce.h \
    wizardSelectPy.h \
    antennaCell.h \
    searchAction.h \
    sqliteManage.h \
    config.h \
    macrodefined.h \
    parsejson.h \
    designtab.h \
    modelfile.h \
    wizardOptimizeAlg.h \
    wizardOptimizeVariables.h \
    optimizeWizard.h \
    wizardOptimizeGainAxialLoss.h \
    optimizetab.h \
    designRun.h \
    optimizeRun.h

FORMS    += mainwindow.ui
