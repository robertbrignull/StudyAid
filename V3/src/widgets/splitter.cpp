#include <iostream>

#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>

#include "widgets/splitter.h"

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent)
{

}

QSplitterHandle *Splitter::createHandle()
{
    return new SplitterHandle(orientation(), this);
}

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter *splitter)
    : QSplitterHandle(orientation, splitter)
{
    if (orientation == Qt::Horizontal) {
        setFixedWidth(10);
    }
    else {
        setFixedHeight(10);
    }
}

void SplitterHandle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (orientation() == Qt::Horizontal) {
        painter.setPen(QPen(QBrush(Qt::gray), 1));
        painter.drawLine(1, 1, 1, size().height());
        painter.drawLine(size().width()-1, 1, size().width()-1, size().height());

        painter.setPen(QPen(QBrush(Qt::gray), 2));
        painter.drawPoint(size().width()/2, size().height()/2 - 10);
        painter.drawPoint(size().width()/2, size().height()/2);
        painter.drawPoint(size().width()/2, size().height()/2 + 10);
    }
    else {
        painter.setPen(QPen(QBrush(Qt::gray), 1));
        painter.drawLine(1, 1, size().width(), 1);
        painter.drawLine(1, size().height()-1, size().width(), size().height()-1);

        painter.setPen(QPen(QBrush(Qt::gray), 2));
        painter.drawPoint(size().width()/2 - 10, size().height()/2);
        painter.drawPoint(size().width()/2, size().height()/2);
        painter.drawPoint(size().width()/2 + 10, size().height()/2);
    }
}