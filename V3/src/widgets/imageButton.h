#pragma once

#include <QPushButton>
#include <QPixmap>
#include <QSize>
#include <QPen>
#include <QBrush>

class QEvent;
class QMouseEvent;
class QPaintEvent;

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    ImageButton(QPixmap pixmap, QSize imageSize, QWidget *parent = 0);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);

private:
    QPixmap pixmap;
    QSize imageSize;

    bool hovering, pressing;

    int border;
};