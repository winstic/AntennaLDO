#include <QDebug>
#include "xmldomdocument.h"

xmlDomDocument::xmlDomDocument(QString fileName){
    this->fileName = fileName;
}

int xmlDomDocument::writeXml(){
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return -2;
    QTextStream out(&file);
    QDomDocument doc;
    QDomElement root, element;
    QDomText text;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version = \'1.0\' encoding = \'UTF-8\'");
    doc.appendChild(instruction);

    //project
    root = doc.createElement("project");
    doc.appendChild(root);

    element = doc.createElement("projectName");
    text = doc.createTextNode(fileName);
    element.appendChild(text);
    root.appendChild(element);

    //data
    QDomElement dataElement = doc.createElement("data");
    root.appendChild(dataElement);

    element = doc.createElement("info");
    text = doc.createTextNode("模型简介");
    element.appendChild(text);
    dataElement.appendChild(element);

    //designs
    QDomElement designsElement = doc.createElement("designs");
    dataElement.appendChild(designsElement);
    designsElement.setAttribute("id", "01");

    element = doc.createElement("performance");
    text = doc.createTextNode("性能指标");
    element.appendChild(text);
    designsElement.appendChild(element);

    //group
    QDomElement groupElement = doc.createElement("group");
    designsElement.appendChild(groupElement);

    QDomElement designElement = doc.createElement("design");
    text = doc.createTextNode("设计1");
    designElement.appendChild(text);
    groupElement.appendChild(designElement);
    designElement.setAttribute("id", "01-01");

    element = doc.createElement("result");
    text = doc.createTextNode("结果查看");
    element.appendChild(text);
    designsElement.appendChild(element);
    // /group
    // /designs /data   /project
    doc.save(out, 4);   //4 spaces
    return 0;
}

int xmlDomDocument::readXml(){
    QDomDocument doc;
    QFile file(fileName);
    QString error = "";
    int row = 0, column = 0;
    if(!file.open(QIODevice::ReadOnly))
        return -2;
    if(!doc.setContent(&file, false, &error, &row, &column)){
        qDebug() << "parse file failed:" << row << "---" << column << ":" << error;
        file.close();
        return -1;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode node, dataNode, designsNode, listNode;
    node = root.firstChildElement();
    QDomElement element, dataElement, designsElement, listElement;
    QDomNodeList designList;
    while(!node.isNull()){
        element = node.toElement();
        if(!element.isNull()){
            if("data" == element.tagName()){
                dataNode = element.firstChildElement();
                while (!dataNode.isNull()) {
                    dataElement = dataNode.toElement();
                    if(!dataElement.isNull()){
                        if("designs" == dataElement.tagName()){
                            if(dataElement.hasAttribute("id")){
                                qDebug() << "---id:" << dataElement.attributeNode("id").value();
                            }
                            designsNode = dataElement.firstChildElement();
                            while(!designsNode.isNull()){
                                designsElement = designsNode.toElement();
                                if(!designsElement.isNull()){
                                    if("group" == designsElement.tagName()){
                                        designList = designsElement.childNodes();
                                        for(int index = 0; index < designList.count(); ++index){
                                            listNode = designList.item(index);
                                            listElement = listNode.toElement();
                                            if(listElement.hasAttribute("id")){
                                                qDebug() << "---------id:" << listElement.attributeNode("id").value() << ":" << listElement.text();
                                            }
                                        }
                                    }
                                    else{
                                        qDebug() << "------" << designsElement.tagName() << ":" << designsElement.text();
                                    }
                                }
                                designsNode = designsNode.nextSibling();
                            }
                        }
                        else{
                            qDebug() << "---" << dataElement.tagName() << ":" << dataElement.text();
                        }
                    }
                    dataNode = dataNode.nextSibling();
                }
            }
            else{
                qDebug() << element.tagName() << ":" << element.text();
            }
        }
        node = node.nextSibling();
    }
    return 0;
}
