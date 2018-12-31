#ifndef ALBUM_H
#define ALBUM_H

#include <QString>

#include "gallery_core_global.h"

class GALLERY_CORESHARED_EXPORT Album
{

public:
    explicit Album(const QString& name = "");

    int id() const { return mId; }
    void setId(int id) { mId = id; }
    QString name() const { return mName; }
    void setName(const QString& name) { mName = name; }

private:
    int mId;
    QString mName;
};

#endif // ALBUM_H
