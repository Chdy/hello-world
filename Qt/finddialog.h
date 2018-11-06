//
// Created by 邓岩 on 2018/10/31.
//

#ifndef QT_FINDDIALOG_H
#define QT_FINDDIALOG_H
# include <QDialog>
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class FindDialog : public QDialog {
    Q_OBJECT;
public:
    FindDialog(QWidget * parent = 0);
signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString &text);
private:
    QLabel * label;
    QLineEdit * lineEdit;
    QCheckBox * caseCheckBox;
    QCheckBox * backwardCheckBox;
    QPushButton * findButton;
    QPushButton * closeButton;
};
#endif //QT_FINDDIALOG_H
