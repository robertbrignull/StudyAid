#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>
#include <QSize>

class QResizeEvent;
class QPaintEvent;

class ResizableImage : public QWidget
{
    Q_OBJECT

public:
    ResizableImage(std::string filename, QWidget *parent = 0);

    void setWidth(int width);
    void reloadImage();

    QSize sizeHint() const;

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);

private:
    std::string filename;
    QPixmap image, scaledImage;
    QSize imageSize;
};