#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>
#include <QDialog>
#include <QScrollArea>

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



    CourseAddPage *courseAddPage = new CourseAddPage();
    courseAddDialog = new QDialog(this);
    courseAddDialog->setModal(true);

    QHBoxLayout *courseAddLayout = new QHBoxLayout(courseAddDialog);
    courseAddLayout->addWidget(courseAddPage);



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



    innerLayout->addSpacing(20);
    innerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 3));
    innerLayout->addSpacing(20);



    QPushButton *newCourseButton = new QPushButton("Add a new course");
    QFont buttonFont = newCourseButton->font();
    buttonFont.setPointSize(24);
    newCourseButton->setFont(buttonFont);
    newCourseButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QHBoxLayout *newCourseLayout = new QHBoxLayout();
    newCourseLayout->addStretch(1);
    newCourseLayout->addWidget(newCourseButton);
    newCourseLayout->addStretch(1);

    innerLayout->addLayout(newCourseLayout);



    innerLayout->addSpacing(10);



    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    
    scrollArea->setWidget(scrollWidget);
    innerLayout->addWidget(scrollArea);

    scrollLayout->addWidget(new ExpandingWidget(QColor(66, 139, 202), new CourseTitleWidget(), new CourseStatsWidget()));
    scrollLayout->addWidget(new ExpandingWidget(QColor(66, 139, 202), new CourseTitleWidget(), new CourseStatsWidget()));
    scrollLayout->addWidget(new ExpandingWidget(QColor(66, 139, 202), new CourseTitleWidget(), new CourseStatsWidget()));

    scrollLayout->addStretch(1);



    connect(newCourseButton, &QPushButton::clicked, [=](){
        courseAddDialog->show();
    });

    connect(courseAddPage, &CourseAddPage::courseAdded, [=](int id){
        courseAddDialog->close();
    });

    connect(courseAddPage, &CourseAddPage::cancelled, [=](){
        courseAddDialog->close();
    });
}