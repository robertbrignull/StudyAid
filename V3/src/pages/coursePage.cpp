#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QScrollArea>

#include "model.h"
#include "database/methods.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/splitter.h"
#include "widgets/dialog.h"
#include "views/factListView.h"
#include "views/sectionPickerWidget.h"
#include "views/breadCrumbs.h"
#include "forms/courseForm.h"
#include "forms/factForm.h"

#include "pages/coursePage.h"

CoursePage::CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    courseEditForm = new CourseForm();
    courseEditDialog = new Dialog(this, courseEditForm, "Edit the course...", "Change", "Cancel");

    courseDeleteDialog = new Dialog(this, nullptr, "Are you sure you want to delete this course?", "Delete", "Cancel");

    factAddForm = new FactForm();
    factAddDialog = new Dialog(this, factAddForm, "Add a new fact...", "Add", "Cancel");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    //  ##   ## #######   ###   #####   ####### #####
    //  ##   ## ##       ## ##  ##  ##  ##      ##  ##
    //  ##   ## ##      ##   ## ##   ## ##      ##   ##
    //  ####### #####   ##   ## ##   ## #####   ##  ##
    //  ##   ## ##      ####### ##   ## ##      #####
    //  ##   ## ##      ##   ## ##  ##  ##      ##  ##
    //  ##   ## ####### ##   ## #####   ####### ##   ##

    // The breadcrumbs show the current course and provide
    // a way to go back to the courses screen.
    // It is presented like a filepath.

    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    breadCrumbs = new BreadCrumbs(1, model, pageStack);
    breadCrumbs->setFixedWidth(700);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(breadCrumbs);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    // Now show the name of the current course and some buttons to
    // edit or delete it.

    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    courseLabel = new QLabel();
    QFont courseFont = courseLabel->font();
    courseFont.setPointSize(38);
    courseLabel->setFont(courseFont);

    editCourseButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editCourseVLayout = new QVBoxLayout();
    editCourseVLayout->addSpacing(16);
    editCourseVLayout->addWidget(editCourseButton);

    deleteCourseButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteCourseVLayout = new QVBoxLayout();
    deleteCourseVLayout->addSpacing(16);
    deleteCourseVLayout->addWidget(deleteCourseButton);

    topLayout->addWidget(courseLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(editCourseVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteCourseVLayout);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);


    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    outerLayout->addSpacing(20);



    //  ######   #####  #####   ##    ##
    //  ##   ## ##   ## ##  ###  ##  ##
    //  ##   ## ##   ## ##   ##   ####
    //  ######  ##   ## ##   ##    ##
    //  ##   ## ##   ## ##   ##    ##
    //  ##   ## ##   ## ##  ###    ##
    //  ######   #####  #####      ##

    // Use a horizontal splitter to divide the two areas dynamically

    splitter = new Splitter(Qt::Horizontal);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    // The section picker controls which section is shown
    // on the other view.

    QScrollArea *pickerScrollArea = new QScrollArea();
    pickerScrollArea->setWidgetResizable(true);
    pickerScrollArea->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(pickerScrollArea);

    QWidget *pickerScrollWidget = new QWidget();
    pickerScrollLayout = new QVBoxLayout(pickerScrollWidget);
    pickerScrollArea->setWidget(pickerScrollWidget);

    pickerScrollLayout->addStretch(1);



    // This is a list of facts which on click will either expand
    // or change to the fact page.

    QScrollArea *courseScrollArea = new QScrollArea();
    courseScrollArea->setWidgetResizable(true);
    courseScrollArea->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(courseScrollArea);

    QWidget *courseScrollWidget = new QWidget();
    courseScrollLayout = new QVBoxLayout(courseScrollWidget);
    courseScrollArea->setWidget(courseScrollWidget);



    splitter->setSizes(QList<int>({0, 1}));



    //  #####  ####  #####  ##   ##   ###   ##       #####
    // ##   ##  ##  ##   ## ###  ##  ## ##  ##      ##   ##
    //  ##      ##  ##      ###  ## ##   ## ##       ##
    //   ###    ##  ##      ####### ##   ## ##        ###
    //     ##   ##  ##  ### ##  ### ####### ##          ##
    // ##   ##  ##  ##   ## ##  ### ##   ## ##      ##   ##
    //  #####  ####  #####  ##   ## ##   ## #######  #####

    connect(editCourseButton, SIGNAL(clicked()), this, SLOT(courseEditButtonClicked()));

    connect(courseEditDialog, SIGNAL(completed()), this, SLOT(courseEditDialogCompleted()));
    connect(courseEditDialog, SIGNAL(cancelled()), courseEditDialog, SLOT(close()));

    connect(deleteCourseButton, SIGNAL(clicked()), courseDeleteDialog, SLOT(show()));

    connect(courseDeleteDialog, SIGNAL(completed()), this, SLOT(courseDeleteDialogAccepted()));
    connect(courseDeleteDialog, SIGNAL(cancelled()), courseDeleteDialog, SLOT(close()));

    connect(factAddDialog, SIGNAL(cancelled()), factAddDialog, SLOT(close()));
    connect(factAddDialog, SIGNAL(completed()), this, SLOT(factAddFormCompleted()));

    connect(model, SIGNAL(courseSelectedChanged(Course)), this, SLOT(courseSelectedChangedSlot(Course)));
    connect(model, SIGNAL(courseEdited(Course)), this, SLOT(courseEditedSlot(Course)));
}

//   #####  ##       #####  ########  #####
//  ##   ## ##      ##   ##    ##    ##   ##
//   ##     ##      ##   ##    ##     ##
//    ###   ##      ##   ##    ##      ###
//      ##  ##      ##   ##    ##        ##
//  ##   ## ##      ##   ##    ##    ##   ##
//   #####  #######  #####     ##     #####

void CoursePage::courseEditButtonClicked()
{
    courseEditForm->setData(model->getCourseSelected());
    courseEditDialog->show();
}

void CoursePage::courseEditDialogCompleted()
{
    Course course = courseEditForm->getData();
    
    editCourse(course);
    model->editCourse(course);

    courseEditDialog->close();
}

void CoursePage::courseDeleteDialogAccepted()
{
    deleteCourse(model->getCourseSelected().id);

    model->deleteCourse(model->getCourseSelected().id);

    courseDeleteDialog->close();
    pageStack->setCurrentIndex(0);
}

void CoursePage::factAddFormCompleted()
{
    Fact data = factAddForm->getData();

    Fact newFact = findFact(addFact(data.parent, data.name, data.type));

    model->addFact(newFact);

    factAddDialog->close();

    if (newFact.type != "Section") {
        model->setFactSelected(newFact);
        pageStack->setCurrentIndex(2);
    }
}

void CoursePage::courseSelectedChangedSlot(Course course)
{
    // Update the labels with the name of the course
    courseLabel->setText(QString::fromStdString(course.name));

    // Rebuild the section picker
    while (pickerScrollLayout->count() > 0) {
        delete pickerScrollLayout->takeAt(0)->widget();
    }
    sectionPicker = new SectionPickerWidget(findFact(course.root_fact), model, pageStack, factAddForm, factAddDialog);
    pickerScrollLayout->addWidget(sectionPicker);
    pickerScrollLayout->addStretch(1);

    // Rebuild the fact list
    while (courseScrollLayout->count() > 0) {
        delete courseScrollLayout->takeAt(0)->widget();
    }
    factListView = new FactListView(course, model, pageStack);
    courseScrollLayout->addWidget(factListView);
    courseScrollLayout->addStretch(1);

    // Connect the two together
    connect(sectionPicker, SIGNAL(sectionSelected(int)), factListView, SLOT(selectSection(int)));

    // Adjust the size of the splitter panes
    splitter->setSizes(QList<int>({pickerScrollLayout->sizeHint().width() + 50, splitter->width() - pickerScrollLayout->sizeHint().width() - 50}));
}

void CoursePage::courseEditedSlot(Course course)
{
    if (model->isCourseSelected() && model->getCourseSelected().id == course.id) {
        // Update the labels with the name of the course
        courseLabel->setText(QString::fromStdString(course.name));
    }
}