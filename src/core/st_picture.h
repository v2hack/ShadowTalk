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

    /* 设置显示大图 */
    Q_INVOKABLE void displayNormalPicture(QString friendIndex, QString messageIndex);

    /* 将图片生成为文件 s*/
    static void writePictureFile(std::string fileName, std::string data);

    /* 查找图片缓存 */
    static std::string findPictureCache(QString fidx, QString midx);

    /* 将文件持久化，并返回文件的存放路径 */
    static QUrl displayPicture(QString friendIndex, QString messageIndex, std::string pictureData);

    /* 缩放图片计算 */
    static int shrinkPicture(QString filePath, int &height, int &width, int limit);
};

#endif // PICTURE_H
