#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class FactListView;
class QVBoxLayout;
class QLabel;
class ExpandingFactWidget;
class ImageButton;

class FactList : public QWidget
{
    Q_OBJECT

public:
    FactList(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactListView *factListView, QWidget *parent = 0);
    ~FactList();

    void paintEvent(QPaintEvent *);

    QWidget *generateFactListOrExpandingFactWidget(Fact fact);
    void insertFactWidget(Fact fact, QWidget *widget);

    void buildLayout(bool isRootSection);
    void destroyLayout();



    Fact fact;
    Model *model;
    ResizableStackedWidget *pageStack;

    // The FactListView this widget belongs to
    FactListView *factListView;

    // Is this list current built and visible
    bool isCurrentlyBuilt;

    // Is this list currently the root, if so don't paint the outline
    bool isRootSection;

    QVBoxLayout *layout;

    // A map from ids to FactLists, always contains all child sections of
    // this section whether or not the widget is currently built.
    std::map<int, FactList*> idChildSectionMap;

    // A map from ids to ExpandingFactWidget, always contains all child facts of
    // this section that are not sections whether or not the widget is currently built.
    std::map<int, ExpandingFactWidget*> idChildFactMap;

    // A map from ids to all of the children currently in the layout
    std::map<int, std::pair<Fact, QWidget*> > idChildMap;

    QLabel *sectionNameLabel;

    Fact moveFact;
    ImageButton *moveButton, *moveAboveButton, *moveBelowButton;
    bool inMoveMode;

signals:
    void moveButtonClicked(Fact fact);
    void moveCompleted();

public slots:
    void moveButtonClickedSlot();
    void moveAboveButtonClickedSlot();
    void moveBelowButtonClickedSlot();

    void activateMoveMode(Fact fact);
    void deactivateMoveMode();

    void factAddedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factOrderingEditedSlot(Fact fact);
    void factDeletedSlot(int id);
};