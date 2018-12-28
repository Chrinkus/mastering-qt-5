#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>

#include "sysinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow},
    mCpuWidget{this},
    mMemoryWidget{this}
{
    ui->setupUi(this);
    SysInfo::instance().init();
    ui->centralWidget->setLayout(new QHBoxLayout());	// errata addition
    ui->centralWidget->layout()->addWidget(&mCpuWidget);
    ui->centralWidget->layout()->addWidget(&mMemoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
