#include <iostream>

#include <map>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>
#include <QScrollArea>

#include "model.h"
#include "database/methods.h"
#include "widgets/courseTitleWidget.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/imageButton.h"
#include "dialogs/formDialog.h"
#include "forms/courseForm.h"

#include "pages/rootPage.h"

RootPage::RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    FormDialog *courseAddDialog = new FormDialog(this, new CourseForm(), "Add a new course...", "Add");



    QHBoxLayout *outerLayout = new QHBoxLayout(this);

    QWidget *innerWidget = new QWidget();
    QVBoxLayout *innerLayout = new QVBoxLayout(innerWidget);
    innerWidget->setFixedWidth(700);

    outerLayout->addStretch(1);
    outerLayout->addWidget(innerWidget, 1);
    outerLayout->addStretch(1);



    QLabel *titleLabel = new QLabel("Study Aid");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(64);
    titleFont.setBold(true);
    titleFont.setFamily("Helvetica");
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    innerLayout->addWidget(titleLabel);



    QLabel *coursesLabel = new QLabel("Courses...");
    QFont coursesFont = coursesLabel->font();
    coursesFont.setPointSize(38);
    coursesLabel->setFont(coursesFont);

    ImageButton *newCourseButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(32, 32));
    QVBoxLayout *newCourseVLayout = new QVBoxLayout();
    newCourseVLayout->addSpacing(16);
    newCourseVLayout->addWidget(newCourseButton);

    QHBoxLayout *newCourseHLayout = new QHBoxLayout();
    newCourseHLayout->addSpacing(10);
    newCourseHLayout->addWidget(coursesLabel);
    newCourseHLayout->addStretch(1);
    newCourseHLayout->addLayout(newCourseVLayout);
    newCourseHLayout->addSpacing(22);

    innerLayout->addLayout(newCourseHLayout);



    innerLayout->addSpacing(20);
    innerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    innerLayout->addSpacing(20);



    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);
    
    scrollArea->setWidget(scrollWidget);
    innerLayout->addWidget(scrollArea);

    std::vector<Course> courses = findAllCourses();
    courseWidgetMap = std::map<int, std::pair<CourseTitleWidget*, int> >();

    for (size_t i = 0; i < courses.size(); ++i) {
        CourseTitleWidget *courseTitleWidget = new CourseTitleWidget(courses[i].name);
        scrollLayout->addWidget(courseTitleWidget);

        courseWidgetMap.insert(std::pair<int, std::pair<CourseTitleWidget*, int> >(courses[i].id, std::pair<CourseTitleWidget*, int>(courseTitleWidget, courses[i].ordering)));

        connect(courseTitleWidget, &CourseTitleWidget::viewButtonClicked, [=](){
            model->setCourseSelected(courses[i]);
            pageStack->setCurrentIndex(1);
        });
    }

    scrollLayout->addStretch(1);



    connect(newCourseButton, &QPushButton::clicked, [=](){
        courseAddDialog->show();
    });

    connect(courseAddDialog, &FormDialog::completed, [=](std::map<std::string, std::string> data){
        Course course = findCourse(addCourse(data.at("name")));

        courseAddDialog->close();
        model->addCourse(course);
        model->setCourseSelected(course);
        pageStack->setCurrentIndex(1);
    });

    connect(courseAddDialog, &FormDialog::cancelled, [=](){
        courseAddDialog->close();
    });



    connect(model, &Model::courseAdded, [=](Course course){
        int i = courseWidgetMap.size();

        if (i != 0) {
            for (auto it = courseWidgetMap.begin(); it != courseWidgetMap.end(); ++it) {
                int j = scrollLayout->indexOf(it->second.first);
                if (it->second.second > course.ordering && j < i) {
                    i = j;
                }
            }
        }

        CourseTitleWidget *courseTitleWidget = new CourseTitleWidget(course.name);
        scrollLayout->insertWidget(i, courseTitleWidget);

        courseWidgetMap.insert(std::pair<int, std::pair<CourseTitleWidget*, int> >(course.id, std::pair<CourseTitleWidget*, int>(courseTitleWidget, course.ordering)));

        connect(courseTitleWidget, &CourseTitleWidget::viewButtonClicked, [=](){
            model->setCourseSelected(course);
            pageStack->setCurrentIndex(1);
        });
    });

    connect(model, &Model::courseEdited, [=](Course course){
        CourseTitleWidget *courseTitleWidget = courseWidgetMap.at(course.id).first;
        int i = scrollLayout->indexOf(courseTitleWidget);

        scrollLayout->removeWidget(courseTitleWidget);
        delete courseTitleWidget;

        courseWidgetMap.erase(course.id);

        courseTitleWidget = new CourseTitleWidget(course.name);
        scrollLayout->insertWidget(i, courseTitleWidget);

        courseWidgetMap.insert(std::pair<int, std::pair<CourseTitleWidget*, int> >(course.id, std::pair<CourseTitleWidget*, int>(courseTitleWidget, course.ordering)));

        connect(courseTitleWidget, &CourseTitleWidget::viewButtonClicked, [=](){
            model->setCourseSelected(course);
            pageStack->setCurrentIndex(1);
        });
    });

    connect(model, &Model::courseDeleted, [=](int id){
        CourseTitleWidget *courseTitleWidget = courseWidgetMap.at(id).first;

        scrollLayout->removeWidget(courseTitleWidget);
        delete courseTitleWidget;

        courseWidgetMap.erase(id);
    });
}