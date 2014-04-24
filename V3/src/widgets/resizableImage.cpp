#include <iostream>

#include <QPainter>

#include "widgets/resizableImage.h"

ResizableImage::ResizableImage(std::string filename, QWidget *parent)
    : QWidget(parent)
{
    this->filename = filename;

    image = QPixmap(QString::fromStdString(filename));

    imageLoaded = (image.width() != 0);

    if (imageLoaded) {
        scaledImage = image.scaledToWidth(image.width());
    }

    border = 11;

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
}

QSize ResizableImage::sizeHint() const
{
    if (imageLoaded) {
        QSize size = scaledImage.size();
        size.setWidth(size.width() + border*2);
        size.setHeight(size.height() + border*2);
        return size;
    }
    else {
        return QSize(0, 0);
    }
}

void ResizableImage::paintEvent(QPaintEvent *)
{
    if (imageLoaded) {
        QPainter painter(this);

        if (scaledImage.width() != std::min(width() - border*2, 1000)) {
            scaledImage = image.scaledToWidth(std::min(width() - border*2, 1000), Qt::SmoothTransformation);
            updateGeometry();
        }

        painter.setBrush(QBrush(Qt::white));
        painter.setPen(QPen(Qt::white));
        painter.drawRect(rect());

        painter.drawPixmap((width() - scaledImage.width()) / 2, border, scaledImage);
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

    if (imageLoaded) {
        scaledImage = image.scaledToWidth(std::min(width(), 1000), Qt::SmoothTransformation);
    }

    updateGeometry();
    repaint();
}