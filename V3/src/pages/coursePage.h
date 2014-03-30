#pragma once

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class QLabel;
class QVBoxLayout;
class QScrollLayout;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

private:
    void rebuildSectionPicker(Course course);
    void rebuildFactList(int id);
    void rebuildCourseDetails(Course course);



    Model *model;
    ResizableStackedWidget *pageStack;
    QLabel *currentCourseLabel, *courseLabel;
    QVBoxLayout *pickerScrollLayout, *courseScrollLayout;
};