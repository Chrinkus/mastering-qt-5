#include "picture.h"

Picture::Picture(const QString& filePath) :
    Picture{QUrl::fromLocalFile(filePath)}
{
}

Picture::Picture(const QUrl& fileUrl) :
    mId{-1},
    mAlbumId{-1},
    mFileUrl{fileUrl}
{
}
