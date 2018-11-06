#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWindow>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include "finddialog.h"
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "gotocelldialog.h"

int main(int argc, char ** argv) {
    QApplication app(argc, argv);
    GoToCellDialog *dialog = new GoToCellDialog;
    dialog->show();
    return app.exec();
}

/*
 * FindDialog * dialog = new FindDialog;
    dialog->show();
 */

/*
 * qmake -project； qmake gotocell.pro
 * 自动绑定信号和槽，通过将slot函数命名为void on_<widget name>_<signal name>(<signal parameters>) 即可将widget name中的信号signal name和这个槽连接起来
 * 一般情况下，在对话框里的子控件，许可器和布局管理器由 Qt 自己管理，其他还要程序员小心删除
 * QVBoxLayout 垂直布局控件
 * QHBoxLayout 水平布局控件
 * 使用new创建控件时，如果指定了一个父控件参数，那么该新创建的控件会存放在父控件中
 * 可以直接通过uic命令将ui文件生成.h文件
 */