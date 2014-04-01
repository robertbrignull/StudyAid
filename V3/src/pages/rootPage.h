#pragma once

#include <map>

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class FormDialog;
class QVBoxLayout;
class CourseTitleWidget;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

public slots:
    void courseViewButtonClicked(Course course);

    void courseAddDialogCompleted(std::map<std::string, std::string> data);

    void courseAddedSlot(Course course);
    void courseEditedSlot(Course course);
    void courseDeletedSlot(int id);

private:
    Model *model;
    ResizableStackedWidget *pageStack;

    // The dialog for adding a new course
    FormDialog *courseAddDialog;

    // The layout that contains the courses
    QVBoxLayout *scrollLayout;
    
    // Maps from ids to Courses and CourseTitleWidgets
    std::map<int, std::pair<Course, CourseTitleWidget*> > idCourseMap;
};