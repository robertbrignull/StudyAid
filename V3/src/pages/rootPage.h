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
class QPushButton;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    QPushButton *newWindowButton;

    ImageButton *newCourseButton;
    CourseForm *courseAddForm;
    Dialog *courseAddDialog;

    // The layout that contains the courses
    QVBoxLayout *scrollLayout;
    
    // Maps from ids to Courses and CourseTitleWidgets
    std::map<int, CourseTitleWidget*> idCourseMap;

signals:
    void requestNewWindow(int pageIndex, Course course, Fact fact, Proof proof);

    void moveButtonClicked(Course course);
    void moveCompleted();

public slots:
    void courseAddDialogCompleted();

    void newWindowButtonClicked();

    void courseAddedSlot(Course course);
    void courseOrderingEditedSlot(Course course);
    void courseDeletedSlot(int id);

private:
    void insertCourseTitleWidget(CourseTitleWidget *courseTitleWidget);
};