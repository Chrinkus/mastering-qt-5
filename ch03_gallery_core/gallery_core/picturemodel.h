#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery_core_global.h"
#include "picture.h"

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERY_CORESHARED_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };

    PictureModel(const AlbumModel& albumModel, QObject* parent = nullptr);

    QModelIndex addPicture(const Picture& picture);

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int,QByteArray> roleNames() const override;

    void setAlbumId(int albumId);
    void clearAlbum();

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDb;
    int mAlbumId;
    std::vector<std::unique_ptr<Picture>> mPictures;
};

#endif // PICTUREMODEL_H