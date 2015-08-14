#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDebug>

#include "st_parsexml.h"

ParseXml::ParseXml() {

}

ParseXml::~ParseXml() {

}

int ParseXml::parseContactXml(QDomElement &array) {
    QDomNode n = array.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            qDebug() << "Element name: " << e.tagName();
            break;
        }
        n = n.nextSibling();
    }
    return 0;
}

int ParseXml::parseQrChannelXml(QDomElement &array) {
    QDomNode n = array.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            qDebug() << "Element name: " << e.tagName();
            break;
        }
        n = n.nextSibling();
    }
    return 0;
}


int ParseXml::parseKeyValueXml(QDomElement &array) {
    QDomNode n = array.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            qDebug() << "Element name: " << e.tagName();
            break;
        }
        n = n.nextSibling();
    }
    return 0;
}


int ParseXml::parseDencryptXml(const QString plainData) {

    QDomDocument document;
    QString strError;
    int errLin = 0, errCol = 0;

    if (!document.setContent(plainData, false, &strError, &errLin, &errCol)) {
        qDebug() << "parse file failed at line " << errLin << " column " << errCol << " " << strError;
        return -1;
    }

    if (document.isNull()) {
        qDebug() << "document is null";
        return -1;
    }

    QDomElement plist = document.documentElement();
    qDebug() << "root - " << plist.tagName();

    QDomElement rootArray = plist.firstChildElement("array");
    qDebug() << "root - " << rootArray.tagName();

    QDomElement elt = rootArray.firstChildElement("array");
    QDomElement array[3];
    for (int i = 0; !elt.isNull(); elt = elt.nextSiblingElement("array"), i++) {
        if (elt.isNull()) {
            qDebug() << "can't find the array child";
            return -1;
        } else {
            array[i] = elt;
            qDebug() << " array - " << elt.tagName();
        }
    }
    return 0;
}
