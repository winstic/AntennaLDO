#ifndef XMLDOMDOCUMENT_H
#define XMLDOMDOCUMENT_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

class xmlDomDocument{
public:
    xmlDomDocument();
    ~xmlDomDocument(){}
    int writeXml(const QString &fileName);
    int readXml(const QString &fileName);

private:
};

#endif // XMLDOMDOCUMENT_H
