#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <QString>
#include <QUrl>


void writePictureFile(std::string fileName, std::string data);
std::string findPictureCache(QString fidx, QString midx);
QUrl displayPicture(QString friendIndex, QString messageIndex, std::string pictureData);
int shrinkPicture(QString filePath, int &height, int &width);

#endif // PICTURE_H
