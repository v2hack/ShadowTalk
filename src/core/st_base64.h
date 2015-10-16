#ifndef BASE64_H
#define BASE64_H

#include <QString>

class Base64
{
public:
    static std::string encode(const std::string &binaryData);
    static std::string decode(const std::string &base64String);

};

#endif // BASE64_H
