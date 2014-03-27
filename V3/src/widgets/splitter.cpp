#include <iostream>

#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "widgets/imageButton.h"

#include "widgets/splitter.h"

const int handleSize = 18;

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent)
{
    setHandleWidth(handleSize);
}

QSplitterHandle *Splitter::createHandle()
{
    return new SplitterHandle(orientation(), this);
}

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter *splitter)
    : QSplitterHandle(orientation, splitter)
{
    if (orientation == Qt::Horizontal) {
        expandButton = new ImageButton(QPixmap(":/images/triangle_left_black.png"), QSize(handleSize-8, handleSize-8), this);
        collapseButton = new ImageButton(QPixmap(":/images/triangle_right_black.png"), QSize(handleSize-8, handleSize-8), this);
    }
    else {
        expandButton = new ImageButton(QPixmap(":/images/triangle_up_black.png"), QSize(handleSize-8, handleSize-8), this);
        collapseButton = new ImageButton(QPixmap(":/images/triangle_down_black.png"), QSize(handleSize-8, handleSize-8), this);
    }

    layoutButtons();

    connect(expandButton, &ImageButton::clicked, [=](){
        moveSplitter(closestLegalPosition(0));
    });

    connect(collapseButton, &ImageButton::clicked, [=](){
        moveSplitter(closestLegalPosition(1000000));
    });
}

void SplitterHandle::resizeEvent(QResizeEvent *)
{
    layoutButtons();
}

void SplitterHandle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    
    painter.setPen(QPen(QBrush(Qt::darkGray), 2));

    if (orientation() == Qt::Horizontal) {
        painter.drawLine(1, 1, 1, size().height());
        painter.drawLine(size().width()-1, 1, size().width()-1, size().height());

        painter.drawLine(2, size().height() - handleSize*2, size().width()-2, size().height() - handleSize*2);
        painter.drawLine(2, size().height() - handleSize, size().width()-2, size().height() - handleSize);
        painter.drawLine(2, size().height(), size().width()-2, size().height());

        painter.drawPoint(size().width()/2, size().height()/2 - 20);
        painter.drawPoint(size().width()/2, size().height()/2 - 10);
        painter.drawPoint(size().width()/2, size().height()/2);
        painter.drawPoint(size().width()/2, size().height()/2 + 10);
        painter.drawPoint(size().width()/2, size().height()/2 + 20);
    }
    else {
        painter.drawLine(1, 1, size().width(), 1);
        painter.drawLine(1, size().height()-1, size().width(), size().height()-1);

        painter.drawLine(size().width() - handleSize*2, 2, size().width() - handleSize*2, size().height()-2);
        painter.drawLine(size().width() - handleSize, 2, size().width() - handleSize, size().height()-2);
        painter.drawLine(size().width(), 2, size().width(), size().height()-2);

        painter.drawPoint(size().width()/2 - 20, size().height()/2);
        painter.drawPoint(size().width()/2 - 10, size().height()/2);
        painter.drawPoint(size().width()/2, size().height()/2);
        painter.drawPoint(size().width()/2 + 10, size().height()/2);
        painter.drawPoint(size().width()/2 + 20, size().height()/2);
    }
}

void SplitterHandle::layoutButtons()
{
    if (orientation() == Qt::Horizontal) {
        expandButton->setGeometry(0, size().height() - handleSize*2, handleSize-8, handleSize-8);
        collapseButton->setGeometry(0, size().height() - handleSize, handleSize-8, handleSize-8);
    }
    else {
        expandButton->setGeometry(size().width() - handleSize*2, 0, handleSize-8, handleSize-8);
        collapseButton->setGeometry(size().width() - handleSize, 0, handleSize-8, handleSize-8);
    }
}