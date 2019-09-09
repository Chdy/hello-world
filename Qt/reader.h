//
// Created by 邓岩 on 2019/6/30.
//

#ifndef QT_READER_H
#define QT_READER_H
////////// reader.h
#include <QObject>
#include <QDebug>

class Reader : public QObject
{
Q_OBJECT
public:
    Reader() {}

    void receiveNewspaper(const QString & name)
    {
        qDebug() << "Receives Newspaper: " << name;
    }
};
#endif //QT_READER_H
