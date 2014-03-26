#pragma once

#include <QSplitter>
#include <QSplitterHandle>

class QPaintEvent;

class Splitter : public QSplitter
{
    Q_OBJECT

public:
    Splitter(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    QSplitterHandle *createHandle();
};

class SplitterHandle : public QSplitterHandle
{
    Q_OBJECT

public:
    SplitterHandle(Qt::Orientation orientation, QSplitter *splitter);

    void paintEvent(QPaintEvent *);
};