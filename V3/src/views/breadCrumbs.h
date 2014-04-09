#pragma once

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class ClickableQLabel;
class QLabel;

class BreadCrumbs : public QWidget
{
    Q_OBJECT

public:
    BreadCrumbs(int level, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);

    QLabel *newSeperator();



    Model *model;
    ResizableStackedWidget *pageStack;

    int level;

    ClickableQLabel *coursesLabel, *factsLabel, *proofsLabel;
    QLabel *currentCourseLabel, *currentFactLabel, *currentProofLabel;

public slots:
    void courseSelectedChangedSlot(Course course);
    void factSelectedChangedSlot(Fact fact);
    void proofSelectedChangedSlot(Proof proof);

    void courseEditedSlot(Course course);
    void factEditedSlot(Fact fact);
    void proofEditedSlot(Proof proof);

    void coursesLabelClicked();
    void factsLabelClicked();
    void proofsLabelClicked();
};