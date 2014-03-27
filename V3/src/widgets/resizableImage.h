#pragma once

#include <QWidget>
#include <QPixmap>
#include <QSize>

class QResizeEvent;
class QPaintEvent;

class ResizableImage : public QWidget
{
    Q_OBJECT

public:
    ResizableImage(QString filename, QWidget *parent = 0);

    void setWidth(int width);
    void reloadImage();

    QSize sizeHint() const;

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QString filename;
    QPixmap image, scaledImage;
    QSize imageSize;
};