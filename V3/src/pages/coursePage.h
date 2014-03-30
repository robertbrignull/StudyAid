#pragma once

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class QLabel;
class QVBoxLayout;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

private:
    void rebuildPage(Course course);



    Model *model;
    ResizableStackedWidget *pageStack;
    QLabel *currentCourseLabel, *courseLabel;
    QVBoxLayout *pickerScrollLayout;
};