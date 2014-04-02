#pragma once

#include <map>

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class CourseForm;
class FormDialog;
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

    CourseForm *courseAddForm;
    FormDialog *courseAddDialog;

    ImageButton *newCourseButton;

    // The layout that contains the courses
    QVBoxLayout *scrollLayout;
    
    // Maps from ids to Courses and CourseTitleWidgets
    std::map<int, std::pair<Course, CourseTitleWidget*> > idCourseMap;

public slots:
    void courseViewButtonClicked(Course course);

    void courseAddDialogCompleted(std::map<std::string, std::string> data);

    void courseAddedSlot(Course course);
    void courseEditedSlot(Course course);
    void courseDeletedSlot(int id);
};