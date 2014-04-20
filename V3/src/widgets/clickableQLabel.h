#pragma once

#include <iostream>

#include <QLabel>

class ClickableQLabel : public QLabel
{
    Q_OBJECT

public:
    ClickableQLabel(QString text, QWidget *parent = 0);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked();
};