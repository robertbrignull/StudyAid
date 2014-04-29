#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class FactList;
class QHBoxLayout;
class FactForm;
class SectionForm;
class Dialog;

class FactListView : public QWidget
{
    Q_OBJECT

public:
    FactListView(Course course, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);
    ~FactListView();



    Course course;
    Model *model;
    ResizableStackedWidget *pageStack;

    std::map<int, FactList*> idFactListMap;
    QHBoxLayout *layout;
    FactList *currentFactList;

    FactForm *factAddForm;
    Dialog *factAddDialog;

    SectionForm *sectionEditForm;
    Dialog *sectionEditDialog;

signals:
    void moveButtonClicked(Fact fact);
    void moveCompleted();

public slots:
    void selectSection(int id);

    void factAddFormCompleted();

    void sectionEditFormCompleted();
};