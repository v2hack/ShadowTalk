#ifndef BASE64_H
#define BASE64_H

#include <QString>



class Base64
{
public:

    static QString encode(const QString &binaryData);
    static QString decode(const QString &base64String);
};

#endif // BASE64_H
