#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <QString>
#include <QUrl>
#include <QObject>

class NormalPicture : public QObject
{
    Q_OBJECT
public:
    explicit NormalPicture(QObject *parent = 0);
    Q_INVOKABLE void displayNormalPicture(QString friendIndex, QString messageIndex);
    static void writePictureFile(std::string fileName, std::string data);
    static std::string findPictureCache(QString fidx, QString midx);
    static QUrl displayPicture(QString friendIndex, QString messageIndex, std::string pictureData);
    static int shrinkPicture(QString filePath, int &height, int &width, int limit);
};

#endif // PICTURE_H
