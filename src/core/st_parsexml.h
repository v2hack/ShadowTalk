#ifndef PARSEXML_H
#define PARSEXML_H
#include <QString>
#include <QDomDocument>


#define SHADOW_SYNC_FILE "SyncPhone.list"

class ParseXml
{
public:
    ParseXml();
    ~ParseXml();

    void writeXmlFile(QString context);

    int parseContactDict(QDomElement dict);
    int parseContactXml(QDomElement &array);

    int parseQrChannelDict(QDomElement dict);
    int parseQrChannelXml(QDomElement &array);

    int parseKeyValueDict(QDomElement dict);
    int parseKeyValueXml(QDomElement &array);

    int parseDencryptXml(const QString plainData);
};

#endif // PARSEXML_H
