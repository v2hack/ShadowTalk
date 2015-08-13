#include "st_parsexml.h"
#include <QString>
#include <QFile>
#include <QDomDocument>

ParseXml::ParseXml() {

}

ParseXml::~ParseXml() {

}



int ParseXml::parseEncryptXml(QString xmlFile) {

    char *filename = xmlFile.toLatin1().data();
    if (NULL == filename) {
        return -1;
    }

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        printf( "open file '%s' failed, error: %s !\n", filename, file.errorString().toStdString().c_str() );
        return -1;
    }

    QDomDocument document;
    QString strError;
    int errLin = 0, errCol = 0;
    if (!document.setContent(&file, false, &strError, &errLin, &errCol)) {
        printf("parse file failed at line %d column %d, error: %s !\n", errLin, errCol, strError.toStdString().c_str());
        return -1;
    }

    if (document.isNull()) {
        printf( "document is null !\n" );
        return -1;
    }

    QDomElement root = document.documentElement();
    printf("%s ", root.tagName().toStdString().c_str());
    if (root.hasAttribute("name")) {
        printf("%s\n", root.attributeNode("name").value().toStdString().c_str());
    }

    QDomElement files = root.firstChildElement();
    if (files.isNull()) {
        return -1;
    } else {
        printf("\t%s\n", files.tagName().toStdString().c_str());
    }

    QDomElement element = files.firstChildElement();
    while (!element.isNull()) {
        if (element.hasAttribute("name")) {
            printf("\t\t file: %s", element.attributeNode("name").value().toStdString().c_str());
        }
        if (element.hasAttribute("size")) {
            printf("\t %s", element.attributeNode("size").value().toStdString().c_str());
        }
        printf("\n");
        element = element.nextSiblingElement();
    }
}
