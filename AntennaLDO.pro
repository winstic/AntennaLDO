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
    Design/designRun.cpp \
    Design/designtab.cpp \
    Design/designWizard.cpp \
    Design/wizardDesignPerformance.cpp \
    Design/wizardDesignVariables.cpp \
    Global/global.cpp \
    MainWindow/antennaCell.cpp \
    MainWindow/atnlibrary.cpp \
    MainWindow/mainwindow.cpp \
    MainWindow/projectWizard.cpp \
    MainWindow/treeModel.cpp \
    MainWindow/wizardAddSetting.cpp \
    MainWindow/wizardIntroduce.cpp \
    MainWindow/wizardSelectPy.cpp \
    Optimize/optimizeRun.cpp \
    Optimize/optimizetab.cpp \
    Optimize/optimizeWizard.cpp \
    Optimize/wizardOptimizeAlg.cpp \
    Optimize/wizardOptimizeGainAxialLoss.cpp \
    Optimize/wizardOptimizeVariables.cpp \
    Utility/modelfile.cpp \
    Utility/parsejson.cpp \
    Utility/searchAction.cpp \
    Utility/sqliteManage.cpp \
    Utility/xmldomdocument.cpp

HEADERS  += Design/designRun.h \
    Design/designtab.h \
    Design/designWizard.h \
    Design/wizardDesignPerformance.h \
    Design/wizardDesignVariables.h \
    Global/config.h \
    Global/global.h \
    Global/macrodefined.h \
    MainWindow/antennaCell.h \
    MainWindow/atnlibrary.h \
    MainWindow/mainwindow.h \
    MainWindow/projectWizard.h \
    MainWindow/treeModel.h \
    MainWindow/wizardAddSetting.h \
    MainWindow/wizardIntroduce.h \
    MainWindow/wizardSelectPy.h \
    Optimize/optimizeRun.h \
    Optimize/optimizetab.h \
    Optimize/optimizeWizard.h \
    Optimize/wizardOptimizeAlg.h \
    Optimize/wizardOptimizeGainAxialLoss.h \
    Optimize/wizardOptimizeVariables.h \
    Utility/modelfile.h \
    Utility/parsejson.h \
    Utility/searchAction.h \
    Utility/sqliteManage.h \
    Utility/xmldomdocument.h

FORMS    += MainWindow/mainwindow.ui
