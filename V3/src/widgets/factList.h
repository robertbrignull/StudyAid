#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class QVBoxLayout;
class QLabel;

class FactList : public QWidget
{
    Q_OBJECT

public:
    FactList(Fact fact, Model *model, ResizableStackedWidget *pageStack, std::map<int, FactList*> *idFactListMap, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

public slots:
    void factAddedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factDeletedSlot(int id);

private:
    void insertFactWidget(Fact fact, QWidget *widget);



    Fact fact;
    Model *model;
    ResizableStackedWidget *pageStack;

    QVBoxLayout *layout;

    // A map from ids to FactLists that is controlled by the FactListView
    std::map<int, FactList*> *idFactListMap;

    // A map from ids to FactLists that is only for children of this fact
    std::map<int, std::pair<Fact, QWidget*> > idChildMap;

    QLabel *sectionNameLabel;
};