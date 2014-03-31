#pragma once

#include <map>

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class QVBoxLayout;
class CourseTitleWidget;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

public slots:
    void courseViewButtonClicked(Course course);

    void addCourseSlot(Course course);
    void editCourseSlot(Course course);
    void deleteCourseSlot(int id);

private:
    Model *model;
    ResizableStackedWidget *pageStack;

    // The layout that contains the courses
    QVBoxLayout *scrollLayout;
    
    // Maps from ids to Courses and CourseTitleWidgets
    std::map<int, std::pair<Course, CourseTitleWidget*> > idCourseMap;
};