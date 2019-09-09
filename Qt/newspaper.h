//
// Created by 邓岩 on 2019/6/30.
//

#ifndef QT_NEWSPAPER_H
#define QT_NEWSPAPER_H
////////// newspaper.h
#include <QObject>
#include <QDebug>
class Newspaper : public QObject
{
Q_OBJECT
public:
    Newspaper(const QString & name) :
            m_name(name)
    {
    }

    void send()
    {
        emit newPaper(m_name);
    }

    signals:
            void newPaper(const QString &name);

private:
    QString m_name;
};
#endif //QT_NEWSPAPER_H
