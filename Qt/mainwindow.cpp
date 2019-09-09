//
// Created by 邓岩 on 2019/6/30.
//

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));

    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    statusBar() ;
}

MainWindow::~MainWindow()
{
}

void MainWindow::open()
{
    QDialog * dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Hello, dialog!"));
    dialog->exec();
    qDebug() << dialog->result();
}