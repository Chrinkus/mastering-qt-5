#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl>
#include <QString>

#include "gallery_core_global.h"

class GALLERY_CORESHARED_EXPORT Picture
{
public:
    Picture(const QString& filePath = "");
    Picture(const QUrl& fileUrl);

    int id() const { return mId; }
    void setId(int id) { mId = id; }

    int albumId() const { return mAlbumId; }
    void setAlbumId(int albumId) { mAlbumId = albumId; }

    QUrl fileUrl() const { return mFileUrl; }
    void setFileUrl(const QUrl& fileUrl) { mFileUrl = fileUrl; }

private:
    int mId;
    int mAlbumId;
    QUrl mFileUrl;
};

#endif // PICTURE_H
