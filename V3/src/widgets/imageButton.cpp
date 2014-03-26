#include <iostream>

#include <QPainter>
#include <QMouseEvent>

#include "widgets/imageButton.h"

ImageButton::ImageButton(QPixmap pixmap, QSize imageSize, QWidget *parent)
    : QPushButton(parent)
{
    this->pixmap = pixmap.scaled(imageSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->imageSize = imageSize;

    pressing = hovering = false;
    border = 4;

    setFixedSize(imageSize.width() + border*2, imageSize.height() + border*2);
}

void ImageButton::enterEvent(QEvent *)
{
    hovering = true;
    repaint();
}

void ImageButton::leaveEvent(QEvent *)
{
    hovering = false;
    repaint();
}

void ImageButton::mousePressEvent(QMouseEvent *)
{
    pressing = true;
    repaint();
    emit pressed();
}

void ImageButton::mouseReleaseEvent(QMouseEvent *event)
{
    pressing = false;
    repaint();

    if (event->x() >= 0 && event->x() < width() &&
        event->y() >= 0 && event->y() < height())
    {
        emit released();
        emit clicked(false);
    }
}

void ImageButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    if (hovering) {
        painter.setPen(QPen(QBrush(QColor(0, 0, 0, 32)), 1));
        painter.setBrush((pressing) ? QBrush(QColor(0, 0, 0, 64)) : QBrush(QColor(0, 0, 0, 0)));
        painter.drawRoundedRect(1, 1, size().width()-1, size().height()-1, 4, 4);
    }

    painter.drawPixmap(border, border, pixmap);
}