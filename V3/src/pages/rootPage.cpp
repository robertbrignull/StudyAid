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
#include "widgets/layout/horizontalSeperator.h"

#include "pages/rootPage.h"

RootPage::RootPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->pageStack = pageStack;



    QHBoxLayout *outerLayout = new QHBoxLayout(this);

    QWidget *innerWidget = new QWidget();
    QVBoxLayout *innerLayout = new QVBoxLayout(innerWidget);

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



    innerLayout->addSpacing(20);
    innerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202)));
    innerLayout->addSpacing(20);



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
    innerLayout->addLayout(buttonLayout);



    innerLayout->addWidget(new ExpandingWidget(QColor(66, 139, 202), new CourseTitleWidget(), new CourseStatsWidget()));
    innerLayout->addWidget(new ExpandingWidget(QColor(66, 139, 202), new CourseTitleWidget(), new CourseStatsWidget()));



    innerLayout->addStretch(1);



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