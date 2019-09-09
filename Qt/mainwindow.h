//
// Created by 邓岩 on 2019/6/30.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void open();

    QAction *openAction;
};

#endif // MAINWINDOW_H