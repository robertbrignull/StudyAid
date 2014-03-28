#include <iostream>

#include <QResizeEvent>
#include <QPainter>

#include "widgets/resizableImage.h"

ResizableImage::ResizableImage(QString filename, QWidget *parent)
    : QWidget(parent)
{
    this->filename = filename;
    image = QPixmap(filename);
    setWidth(image.size().width());

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void ResizableImage::reloadImage()
{
    image = QPixmap(filename);
    scaledImage = image.scaledToWidth(imageSize.width(), Qt::SmoothTransformation);
}

void ResizableImage::setWidth(int width)
{
    if (width > 1000) { width = 1000; }

    scaledImage = image.scaledToWidth(width, Qt::SmoothTransformation);
    imageSize = QSize(width, width * scaledImage.height() / scaledImage.width());
}

QSize ResizableImage::sizeHint() const
{
    return imageSize;
}

void ResizableImage::resizeEvent(QResizeEvent *event)
{
    setWidth(event->size().width());
}

void ResizableImage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, scaledImage);
}