#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <QString>
#include <QUrl>
#include <QObject>

void writePictureFile(std::string fileName, std::string data);
std::string findPictureCache(QString fidx, QString midx);
QUrl displayPicture(QString friendIndex, QString messageIndex, std::string pictureData);
int shrinkPicture(QString filePath, int &height, int &width, int limit);


class NormalPicture : public QObject
{
    Q_OBJECT
public:
    explicit NormalPicture(QObject *parent = 0);
    Q_INVOKABLE void displayNormalPicture(QString friendIndex, QString messageIndex);

signals:

public slots:
};

#endif // PICTURE_H
