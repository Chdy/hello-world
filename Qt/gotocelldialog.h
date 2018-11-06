//
// Created by 邓岩 on 2018/11/5.
//

#ifndef QT_GOTOCELLDIALOG_H
#define QT_GOTOCELLDIALOG_H
#include "ui_gotocelldialog.h"
#include <QDialog>

class GoToCellDialog : public QDialog, public Ui::GoToCellDialog {
    Q_OBJECT
public:
    GoToCellDialog(QWidget * parent = NULL);
public slots:
    void on_lineEdit_textChanged();
};

#endif //QT_GOTOCELLDIALOG_H
