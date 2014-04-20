#include <iostream>

#include <QFont>
#include <QMouseEvent>

#include "widgets/clickableQLabel.h"

ClickableQLabel::ClickableQLabel(QString text, QWidget *parent)
    : QLabel(text, parent)
{

}

void ClickableQLabel::enterEvent(QEvent *)
{
    QFont labelFont = font();
    labelFont.setUnderline(true);
    setFont(labelFont);
}

void ClickableQLabel::leaveEvent(QEvent *)
{
    QFont labelFont = font();
    labelFont.setUnderline(false);
    setFont(labelFont);
}

void ClickableQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->x() >= 0 && event->x() < width() &&
        event->y() >= 0 && event->y() < height())
    {
        emit clicked();
    }
}