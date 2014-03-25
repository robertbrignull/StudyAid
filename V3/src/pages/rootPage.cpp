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
#include "widgets/resizableStackedWidget.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/imageButton.h"

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



    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    
    scrollArea->setWidget(scrollWidget);
    innerLayout->addWidget(scrollArea);

    scrollLayout->addWidget(new CourseTitleWidget(0, "Part A: Linear Algebra"));
    scrollLayout->addWidget(new CourseTitleWidget(0, "Part A: Complex Analysis"));
    scrollLayout->addWidget(new CourseTitleWidget(0, "Part B: Set Theory"));

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