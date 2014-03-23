#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>

#include "pages/courseAddPage.h"
#include "widgets/courseTitleWidget.h"
#include "widgets/courseStatsWidget.h"
#include "widgets/layout/expandingWidget.h"
#include "widgets/layout/resizableStackedWidget.h"

#include "pages/rootPage.h"

RootPage::RootPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->pageStack = pageStack;

    QVBoxLayout *layout = new QVBoxLayout(this);



    QLabel *titleLabel = new QLabel("Study Aid");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(72);
    titleFont.setBold(true);
    titleFont.setUnderline(true);
    titleLabel->setFont(titleFont);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addStretch(1);
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch(1);
    layout->addLayout(titleLayout);



    QPushButton *newCourseButton = new QPushButton("Add a new course");
    QFont buttonFont = newCourseButton->font();
    buttonFont.setPointSize(24);
    newCourseButton->setFont(buttonFont);
    newCourseButton->setMaximumHeight(40);

    newCourseStack = new ResizableStackedWidget();
    connect(newCourseStack, SIGNAL(currentChanged(int)), newCourseStack, SLOT(onCurrentChanged(int)));

    CourseAddPage *courseAddPage = new CourseAddPage();
    
    newCourseStack->addWidget(newCourseButton);
    newCourseStack->addWidget(courseAddPage);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(newCourseStack);
    buttonLayout->addStretch(1);
    layout->addLayout(buttonLayout);





    QHBoxLayout *factsHBoxLayout = new QHBoxLayout();
    QVBoxLayout *factsVBoxLayout = new QVBoxLayout();
    
    factsVBoxLayout->addWidget(new ExpandingWidget(new CourseTitleWidget(), new CourseStatsWidget()));
    factsVBoxLayout->addWidget(new ExpandingWidget(new CourseTitleWidget(), new CourseStatsWidget()));

    factsHBoxLayout->addStretch(1);
    factsHBoxLayout->addLayout(factsVBoxLayout);
    factsHBoxLayout->addStretch(1);
    layout->addLayout(factsHBoxLayout);



    layout->addStretch(1);



    connect(newCourseButton, &QPushButton::clicked, [=](){
        newCourseStack->setCurrentIndex(1);
    });

    connect(courseAddPage, &CourseAddPage::courseAdded, [=](int id){
        newCourseStack->setCurrentIndex(0);
    });

    connect(courseAddPage, &CourseAddPage::cancelled, [=](){
        newCourseStack->setCurrentIndex(0);
    });
}