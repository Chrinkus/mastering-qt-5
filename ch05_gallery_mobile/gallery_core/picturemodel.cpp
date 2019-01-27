#include "picturemodel.h"
#include "databasemanager.h"
#include "albummodel.h"

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
    QAbstractListModel{parent},
    mDb{DatabaseManager::instance()},
    mAlbumId{-1}
{
    connect(&albumModel, &AlbumModel::rowsRemoved,
            this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture& picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex{}, rows, rows);
    auto newPicture = std::make_unique<Picture>(picture);
    mDb.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures.push_back(std::move(newPicture));
    endInsertRows();
    return index(rows, 0);
}

int PictureModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(mPictures.size());
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
    if (!isIndexValid(index))
        return QVariant{};

    const Picture& picture = *mPictures.at(static_cast<size_t>(index.row()));
    switch (role) {
    case Qt::DisplayRole:
        return picture.fileUrl().fileName();
    case Roles::UrlRole:
        return picture.fileUrl();
    case Roles::FilePathRole:
        return picture.fileUrl().toLocalFile();
    default:
        return QVariant{};
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount())
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Picture& picture =
                *mPictures.at(static_cast<size_t>(row + countLeft));
        mDb.pictureDao.removePicture(picture.id());
    }
    mPictures.erase(std::begin(mPictures) + row,
                    std::begin(mPictures) + row + count);
    endRemoveRows();

    return true;
}

QHash<int,QByteArray> PictureModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[Roles::UrlRole] = "url";
    roles[Roles::FilePathRole] = "filepath";
    return roles;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum()
{
    mDb.pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId <= 0) {
        mPictures.clear();
        return;
    }
    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid())
        return false;
    return true;
}
