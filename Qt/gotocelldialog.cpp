//
// Created by 邓岩 on 2018/11/5.
//

#include "gotocelldialog.h"
GoToCellDialog::GoToCellDialog(QWidget *parent) : QDialog(parent)
{

    setupUi(this);

    QRegExp regExp("[1-9][0-9]{3,8}@[A-Za-z]{2,5}\.com");
    lineEdit->setValidator(new QRegExpValidator(regExp, this));
    //connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    //connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged() {

    buttonBox->setEnabled(lineEdit->hasAcceptableInput());
}