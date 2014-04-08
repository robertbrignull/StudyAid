#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class FactList;
class QHBoxLayout;

class FactListView : public QWidget
{
    Q_OBJECT

public:
    FactListView(Course course, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);
    ~FactListView();



    Course course;
    std::map<int, FactList*> idFactListMap;
    QHBoxLayout *layout;
    FactList *currentFactList;

public slots:
    void selectSection(int id);
};