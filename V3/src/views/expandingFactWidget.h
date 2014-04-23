#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class FactListView;
class QMouseEvent;
class ResizableImage;
class QLabel;
class ImageButton;

class ExpandingFactWidget : public QWidget
{
    Q_OBJECT

public:
    ExpandingFactWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactListView *factListView, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);



    Model *model;
    ResizableStackedWidget *pageStack;

    Fact fact;

    FactListView *factListView;

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

    Fact moveFact;
    ImageButton *moveButton, *moveAboveButton, *moveBelowButton;
    bool inMoveMode;

signals:
    void moveButtonClicked(Fact fact);
    void moveCompleted();

public slots:
    void viewButtonClicked();

    void moveButtonClickedSlot();
    void moveAboveButtonClickedSlot();
    void moveBelowButtonClickedSlot();

    void activateMoveMode(Fact fact);
    void deactivateMoveMode();

    void factEditedSlot(Fact fact);
    void factRenderedSlot(Fact fact, bool success);

private:
    void setExpanded(bool expanded);
};