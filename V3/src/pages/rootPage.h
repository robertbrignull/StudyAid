#pragma once

#include <map>

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class CourseForm;
class Dialog;
class QVBoxLayout;
class CourseTitleWidget;
class ImageButton;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    ImageButton *newCourseButton;
    CourseForm *courseAddForm;
    Dialog *courseAddDialog;

    // The layout that contains the courses
    QVBoxLayout *scrollLayout;
    
    // Maps from ids to Courses and CourseTitleWidgets
    std::map<int, std::pair<Course, CourseTitleWidget*> > idCourseMap;

public slots:
    void courseViewButtonClicked(Course course);

    void courseAddDialogCompleted();

    void courseAddedSlot(Course course);
    void courseDeletedSlot(int id);
};