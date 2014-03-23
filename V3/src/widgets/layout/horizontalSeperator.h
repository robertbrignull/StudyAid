#pragma once

#include <QWidget>
#include <QPainter>

class HorizontalSeperator : public QWidget
{
    Q_OBJECT

public:
    HorizontalSeperator(QColor color, QWidget *parent = 0)
        : QWidget(parent)
    {
        this->color = color;

        this->setFixedHeight(3);
    }

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        painter.fillRect(0, 0, size().width(), size().height(), color);
    }

private:
    QColor color;
};