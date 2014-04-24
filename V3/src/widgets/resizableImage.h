#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>
#include <QSize>

class QPaintEvent;

class ResizableImage : public QWidget
{
    Q_OBJECT

public:
    ResizableImage(std::string filename, QWidget *parent = 0);

    void setWidth(int width);

    QSize sizeHint() const;

    void paintEvent(QPaintEvent *);



    std::string filename;
    QPixmap image, scaledImage;
    bool imageLoaded;

    int border;

public slots:
    void setImage(std::string filename);
    void reloadImage();
};