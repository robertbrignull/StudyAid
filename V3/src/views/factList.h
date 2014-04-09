#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class QVBoxLayout;
class QLabel;
class ExpandingFactWidget;

class FactList : public QWidget
{
    Q_OBJECT

public:
    FactList(Fact fact, Model *model, ResizableStackedWidget *pageStack, std::map<int, FactList*> *idFactListMap, QWidget *parent = 0);
    ~FactList();

    void paintEvent(QPaintEvent *);

    QWidget *generateFactListOrExpandingFactWidget(Fact fact);
    void insertFactWidget(Fact fact, QWidget *widget);

    void buildLayout();
    void destroyLayout();



    Fact fact;
    Model *model;
    ResizableStackedWidget *pageStack;

    // Is this list current built and visible
    bool isCurrentlyBuilt;

    QVBoxLayout *layout;

    // A map from ids to FactLists that is controlled by the FactListView
    std::map<int, FactList*> *idFactListMap;

    // A map from ids to FactLists, always contains all child sections of
    // this section whether or not the widget is currently built.
    std::map<int, std::pair<Fact, FactList*> > idChildSectionMap;

    // A map from ids to all of the children currently in the layout
    std::map<int, std::pair<Fact, QWidget*> > idChildMap;

    QLabel *sectionNameLabel;

public slots:
    void factAddedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factDeletedSlot(int id);
};