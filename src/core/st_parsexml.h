#ifndef PARSEXML_H
#define PARSEXML_H
#include <QString>
#include <QDomDocument>

class ParseXml
{
public:
    ParseXml();
    ~ParseXml();

    int parseContactXml(QDomElement &array);
    int parseQrChannelXml(QDomElement &array);
    int parseKeyValueXml(QDomElement &array);
    int parseDencryptXml(const QString plainData);
};

#endif // PARSEXML_H
