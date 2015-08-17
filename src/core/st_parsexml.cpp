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
    QDomElement dict = array.firstChildElement("dict");
    for (int i = 0; !dict.isNull(); dict = dict.nextSiblingElement("dict"), i++) {
        if (dict.isNull()) {
            qDebug() << "can't find the dict child";
            return -1;
        } else {
            qDebug() << " dict - " << dict.tagName() << " i - " << i;
            //            if (parseContactDict(dict) < 0) {
            //                return -1;
            //            }
        }
    }
}


int ParseXml::parseQrChannelDict(QDomElement dict) {
    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            if (e.text() == QString("channelId"))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString("string")) {
                            qDebug() << "[channelId] - " << en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString("createdTime"))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString("date")) {
                            qDebug() << "[createdTime] - " << en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString("expiredTime"))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString("date")) {
                            qDebug() << "[expiredTime] - " << en.text();
                        } else {
                            qDebug() << "[expiredTime] - error " << en.tagName();
//                          return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString("shortCode"))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString("string")) {
                            qDebug() << "[shortCode] - " << en.text();
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }
    return 0;
}


int ParseXml::parseQrChannelXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement("dict");
    for (int i = 0; !dict.isNull(); dict = dict.nextSiblingElement("dict"), i++) {
        if (dict.isNull()) {
            qDebug() << "can't find the dict child";
            return -1;
        } else {
            qDebug() << " dict - " << dict.tagName() << " i - " << i;
            if (parseQrChannelDict(dict) < 0) {
                return -1;
            }
        }
    }
    return 0;
}


int ParseXml::parseKeyValueDict(QDomElement dict) {
    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if (e.tagName() == QString("key")) {
                // qDebug() << "[KeyValue] : key - " << e.text();
                // TODO:
            } else if (e.tagName() == QString("data")) {
                // qDebug() << "[KeyValue] : data - " << e.text();
                // TODO:
            } else {
                return -1;
            }
        }
        n = n.nextSibling();
    }
    return 0;
}

int ParseXml::parseKeyValueXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement("dict");
    for (int i = 0; !dict.isNull(); dict = dict.nextSiblingElement("dict"), i++) {
        if (dict.isNull()) {
            qDebug() << "can't find the dict child";
            return -1;
        } else {
            qDebug() << " dict - " << dict.tagName() << " i - " << i;
            if (parseKeyValueDict(dict) < 0) {
                return -1;
            }
        }
    }
    return 0;
}



void writeXmlFile(QString context)
{
    QFile f("test.txt");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream txtOutput(&f);
	txtOutput << context;
    f.close();
    return;
}


int ParseXml::parseDencryptXml(const QString plainData) {

    QDomDocument document;
    QString strError;
    int errLin = 0, errCol = 0;

    writeXmlFile(plainData);

    if (!document.setContent(plainData, false, &strError, &errLin, &errCol)) {
        qDebug() << "parse file failed at line " << errLin << " column " << errCol << " " << strError;
        return -1;
    }

    if (document.isNull()) {
        qDebug() << "document is null";
        return -1;
    }

    QDomElement plist = document.documentElement();
    QDomElement rootArray = plist.firstChildElement("array");
    QDomElement elt = rootArray.firstChildElement("array");

    QDomElement array[3];
    for (int i = 0; !elt.isNull(); elt = elt.nextSiblingElement("array"), i++) {
        if (elt.isNull()) {
            qDebug() << "can't find the array child";
            return -1;
        } else {
            array[i] = elt;
            qDebug() << " array - " << elt.tagName() << " i - " << i;
        }
    }

	qDebug() << "---------------------------------------------";
    if (parseContactXml(array[0])  < 0) {
        return -1;
    }
    qDebug() << "---------------------------------------------";
    if (parseQrChannelXml(array[1]) < 0) {
        return -1;
    }
    qDebug() << "---------------------------------------------";
    //    if (parseKeyValueXml(array[2]) < 0) {
    //        return -1;
    //    }
    return 0;
}
