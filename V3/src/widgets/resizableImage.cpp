#include <iostream>

#include <QResizeEvent>
#include <QPainter>

#include "widgets/resizableImage.h"

ResizableImage::ResizableImage(std::string filename, QWidget *parent)
    : QWidget(parent)
{
    this->filename = filename;

    image = QPixmap(QString::fromStdString(filename));

    imageLoaded = (image.width() != 0);

    setWidth(image.size().width());

    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
}

void ResizableImage::setWidth(int width)
{
    if (imageLoaded) {
        if (width > 1000) { width = 1000; }

        scaledImage = image.scaledToWidth(width, Qt::SmoothTransformation);
    }
}

QSize ResizableImage::sizeHint() const
{
    if (imageLoaded) {
        return scaledImage.size();
    }
    else {
        return QSize(0, 0);
    }
}

void ResizableImage::resizeEvent(QResizeEvent *event)
{
    setWidth(event->size().width());
}

void ResizableImage::paintEvent(QPaintEvent *)
{
    if (imageLoaded) {
        QPainter painter(this);

        painter.drawPixmap(0, 0, scaledImage);
    }
}

void ResizableImage::setImage(std::string filename)
{
    this->filename = filename;
    reloadImage();
}

void ResizableImage::reloadImage()
{
    image = QPixmap(QString::fromStdString(filename));

    imageLoaded = (image.width() != 0);

    setWidth(1000);

    updateGeometry();
    repaint();
}