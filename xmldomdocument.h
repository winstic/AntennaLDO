#ifndef XMLDOMDOCUMENT_H
#define XMLDOMDOCUMENT_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

class xmlDomDocument{
public:
    xmlDomDocument(QString fileName);
    ~xmlDomDocument(){}
    int writeXml();
    int readXml();    

private:
    QString fileName;
};

#endif // XMLDOMDOCUMENT_H
