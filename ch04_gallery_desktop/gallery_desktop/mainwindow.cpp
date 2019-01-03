#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QItemSelectionModel>

#include "gallerywidget.h"
#include "picturewidget.h"
#include "albummodel.h"
#include "picturemodel.h"
#include "thumbnailproxymodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGalleryWidget{new GalleryWidget{this}},
    mPictureWidget{new PictureWidget{this}},
    mStackedWidget{new QStackedWidget{this}}
{
    ui->setupUi(this);

    auto albumModel = new AlbumModel{this};
    auto albumSelectionModel = new QItemSelectionModel{albumModel, this};
    mGalleryWidget->setAlbumModel(albumModel);
    mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);

    auto pictureModel = new PictureModel{*albumModel, this};
    auto thumbnailModel = new ThumbnailProxyModel{this};
    thumbnailModel->setSourceModel(pictureModel);

    auto pictureSelectionModel = new QItemSelectionModel{thumbnailModel, this};
    mGalleryWidget->setPictureModel(thumbnailModel);
    mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
    mPictureWidget->setModel(thumbnailModel);
    mPictureWidget->setSelectionModel(pictureSelectionModel);

    connect(mGalleryWidget, &GalleryWidget::pictureActivated,
            this, &MainWindow::displayPicture);
    connect(mPictureWidget, &PictureWidget::backToGallery,
            this, &MainWindow::displayGallery);

    mStackedWidget->addWidget(mGalleryWidget);
    mStackedWidget->addWidget(mPictureWidget);
    displayGallery();

    setCentralWidget(mStackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayGallery()
{
    mStackedWidget->setCurrentWidget(mGalleryWidget);
}

void MainWindow::displayPicture(const QModelIndex&)
{
    mStackedWidget->setCurrentWidget(mPictureWidget);
}
