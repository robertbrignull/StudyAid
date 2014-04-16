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
class ImageButton;

class ExpandingFactWidget : public QWidget
{
    Q_OBJECT

public:
    ExpandingFactWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);



    Model *model;
    ResizableStackedWidget *pageStack;

    Fact fact;

    bool expanded;
    double currentHeight;
    ImageButton *viewButton;

    QPixmap image, scaledImage;
    int imageWidth, imageHeight;
    bool imageNeedsScaling;

    QWidget *headWidget;
    int headWidgetHeight;
    QLabel *nameLabel;

    int radius, border;
    QColor headColor, bodyColor, borderColor;

public slots:
    void viewButtonClicked();

    void factEditedSlot(Fact fact);

private:
    void setExpanded(bool expanded);
};