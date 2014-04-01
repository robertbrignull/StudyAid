#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class QMouseEvent;
class ResizableImage;
class QLabel;

class ExpandingFactWidget : public QWidget
{
    Q_OBJECT

public:
    ExpandingFactWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public slots:
    void factEditedSlot(Fact fact);

private:
    void setExpanded(bool expanded);



    Model *model;
    ResizableStackedWidget *pageStack;

    Fact fact;

    bool expanded;
    double currentHeight;
    ResizableImage *image;

    QWidget *headWidget;
    int headWidgetHeight;
    QLabel *nameLabel;

    int radius, border;
    QColor headColor, bodyColor, borderColor;
};