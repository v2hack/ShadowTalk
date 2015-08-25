#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <QString>


void writePictureFile(std::string fileName, std::string data);
std::string findPictureCache(QString fidx, QString midx);
QString displayPicture(QString friendIndex, QString messageIndex, std::string pictureData);

#endif // PICTURE_H
