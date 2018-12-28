#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"

#include <QDebug>
#include <QInputDialog>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled task"),
                                         &ok);
    if (ok && !name.isEmpty()) {
        qDebug() << "Adding new task";
        Task* task = new Task(name);
        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this,
                &MainWindow::taskStatusChanged);
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

void MainWindow::removeTask(Task* task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task*)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    // ala Scott Meyers via Kate Gregory
    auto completedCount = std::count_if(std::begin(mTasks), std::end(mTasks),
                   [](const auto t) { return t->isCompleted(); });

    auto todoCount = mTasks.size() - completedCount;
    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                    .arg(todoCount)
                    .arg(completedCount));
}
