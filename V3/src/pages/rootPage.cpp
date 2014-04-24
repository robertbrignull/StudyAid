#include <iostream>
#include <map>
#include <algorithm>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>
#include <QScrollArea>

#include "model.h"
#include "database/methods.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/imageButton.h"
#include "widgets/dialog.h"
#include "views/courseTitleWidget.h"
#include "forms/courseForm.h"

#include "pages/rootPage.h"

RootPage::RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    courseAddForm = new CourseForm();
    courseAddDialog = new Dialog(this, courseAddForm, "Add a new course...", "Add", "Cancel");



    QHBoxLayout *outerLayout = new QHBoxLayout(this);

    QWidget *innerWidget = new QWidget();
    QVBoxLayout *innerLayout = new QVBoxLayout(innerWidget);
    innerWidget->setFixedWidth(700);

    outerLayout->addStretch(1);
    outerLayout->addWidget(innerWidget, 1);
    outerLayout->addStretch(1);



    //  ##   ## #######   ###   #####   ####### #####
    //  ##   ## ##       ## ##  ##  ##  ##      ##  ##
    //  ##   ## ##      ##   ## ##   ## ##      ##   ##
    //  ####### #####   ##   ## ##   ## #####   ##  ##
    //  ##   ## ##      ####### ##   ## ##      #####
    //  ##   ## ##      ##   ## ##  ##  ##      ##  ##
    //  ##   ## ####### ##   ## #####   ####### ##   ##

    // The title at the top of the page
    QLabel *titleLabel = new QLabel("Study Aid");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(64);
    titleFont.setBold(true);
    titleFont.setFamily("Helvetica");
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    innerLayout->addWidget(titleLabel);

    // The label that says "Courses..."
    QLabel *coursesLabel = new QLabel("Courses...");
    QFont coursesFont = coursesLabel->font();
    coursesFont.setPointSize(38);
    coursesLabel->setFont(coursesFont);

    // The button to open a new window
    newWindowButton = new ImageButton(QPixmap(":/images/open_window_black.png"), QSize(32, 32));
    QVBoxLayout *newWindowVLayout = new QVBoxLayout();
    newWindowVLayout->addSpacing(16);
    newWindowVLayout->addWidget(newWindowButton);

    // The button for adding a new course
    newCourseButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(32, 32));
    QVBoxLayout *newCourseVLayout = new QVBoxLayout();
    newCourseVLayout->addSpacing(16);
    newCourseVLayout->addWidget(newCourseButton);

    // Add them together into a QHBoxLayout
    QHBoxLayout *newCourseHLayout = new QHBoxLayout();
    newCourseHLayout->addSpacing(10);
    newCourseHLayout->addWidget(coursesLabel);
    newCourseHLayout->addStretch(1);
    newCourseHLayout->addLayout(newWindowVLayout);
    newCourseHLayout->addSpacing(10);
    newCourseHLayout->addLayout(newCourseVLayout);
    newCourseHLayout->addSpacing(22);

    innerLayout->addLayout(newCourseHLayout);



    // The blue coloured horizontal seperator
    innerLayout->addSpacing(20);
    innerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    innerLayout->addSpacing(20);



    //  ######   #####  #####   ##    ##
    //  ##   ## ##   ## ##  ###  ##  ##
    //  ##   ## ##   ## ##   ##   ####
    //  ######  ##   ## ##   ##    ##
    //  ##   ## ##   ## ##   ##    ##
    //  ##   ## ##   ## ##  ###    ##
    //  ######   #####  #####      ##

    // The courses list is contained within a scroll area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    // The scroll area needs a single widget as it's contents
    QWidget *scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);

    scrollArea->setWidget(scrollWidget);
    innerLayout->addWidget(scrollArea);



    // Load every course from the database and build up idCourseMap
    std::vector<Course> courses = Database::findAllCourses();
    idCourseMap = std::map<int, CourseTitleWidget*>();

    for (size_t i = 0; i < courses.size(); ++i) {
        courseAddedSlot(courses[i]);
    }

    scrollLayout->addStretch(1);



    //  #####  ####  #####  ##   ##   ###   ##       #####
    // ##   ##  ##  ##   ## ###  ##  ## ##  ##      ##   ##
    //  ##      ##  ##      ###  ## ##   ## ##       ##
    //   ###    ##  ##      ####### ##   ## ##        ###
    //     ##   ##  ##  ### ##  ### ####### ##          ##
    // ##   ##  ##  ##   ## ##  ### ##   ## ##      ##   ##
    //  #####  ####  #####  ##   ## ##   ## #######  #####

    connect(newCourseButton, SIGNAL(clicked()), courseAddDialog, SLOT(show()));

    connect(courseAddDialog, SIGNAL(accepted()), this, SLOT(courseAddDialogCompleted()));
    connect(courseAddDialog, SIGNAL(rejected()), courseAddDialog, SLOT(close()));

    connect(newWindowButton, SIGNAL(clicked()), this, SIGNAL(requestNewWindow()));

    connect(model, SIGNAL(courseAdded(Course)), this, SLOT(courseAddedSlot(Course)));
    connect(model, SIGNAL(courseOrderingEdited(Course)), this, SLOT(courseOrderingEditedSlot(Course)));
    connect(model, SIGNAL(courseDeleted(int)), this, SLOT(courseDeletedSlot(int)));
}

//   #####  ##       #####  ########  #####
//  ##   ## ##      ##   ##    ##    ##   ##
//   ##     ##      ##   ##    ##     ##
//    ###   ##      ##   ##    ##      ###
//      ##  ##      ##   ##    ##        ##
//  ##   ## ##      ##   ##    ##    ##   ##
//   #####  #######  #####     ##     #####

void RootPage::courseAddDialogCompleted()
{
    Course course = model->addCourse(courseAddForm->getData().name);
    model->setCourseSelected(course);

    courseAddDialog->close();
    pageStack->setCurrentIndex(1);
}

void RootPage::courseAddedSlot(Course course)
{
    insertCourseTitleWidget(new CourseTitleWidget(course, model, pageStack));
}

void RootPage::courseOrderingEditedSlot(Course course)
{
    // Update orderings on children
    for (auto it = idCourseMap.begin(); it != idCourseMap.end(); it++) {
        if (it->second->course.id == course.id) {
            it->second->course = course;
        }
        else if (it->second->course.ordering >= course.ordering) {
            it->second->course.ordering += 1;
        }
    }

    // Remove the edited CourseTitleWidget and re-add it
    CourseTitleWidget *courseTitleWidget = idCourseMap.at(course.id);

    scrollLayout->removeWidget(courseTitleWidget);
    idCourseMap.erase(course.id);

    insertCourseTitleWidget(courseTitleWidget);
}

void RootPage::courseDeletedSlot(int id)
{
    CourseTitleWidget *courseTitleWidget = idCourseMap.at(id);

    scrollLayout->removeWidget(courseTitleWidget);
    delete courseTitleWidget;

    idCourseMap.erase(id);
}

//  ##      ## ####### ######## ##    ##  #####  #####    #####
//  ###    ### ##         ##    ##    ## ##   ## ##  ### ##   ##
//  ####  #### ##         ##    ##    ## ##   ## ##   ##  ##
//  ## #### ## #####      ##    ######## ##   ## ##   ##   ###
//  ##  ##  ## ##         ##    ##    ## ##   ## ##   ##     ##
//  ##      ## ##         ##    ##    ## ##   ## ##  ### ##   ##
//  ##      ## #######    ##    ##    ##  #####  #####    #####

void RootPage::insertCourseTitleWidget(CourseTitleWidget *courseTitleWidget)
{
    int position = idCourseMap.size();

    for (auto it = idCourseMap.begin(); it != idCourseMap.end(); it++) {
        if (it->second->course.ordering > courseTitleWidget->course.ordering) {
            position = std::min(position, scrollLayout->indexOf(it->second));
        }
    }

    scrollLayout->insertWidget(position, courseTitleWidget);

    idCourseMap.insert(std::pair<int, CourseTitleWidget*>(courseTitleWidget->course.id, courseTitleWidget));

    connect(courseTitleWidget, SIGNAL(moveButtonClicked(Course)), this, SIGNAL(moveButtonClicked(Course)));
    connect(courseTitleWidget, SIGNAL(moveCompleted()), this, SIGNAL(moveCompleted()));

    connect(this, SIGNAL(moveButtonClicked(Course)), courseTitleWidget, SLOT(activateMoveMode(Course)));
    connect(this, SIGNAL(moveCompleted()), courseTitleWidget, SLOT(deactivateMoveMode()));
}