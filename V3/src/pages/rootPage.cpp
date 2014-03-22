#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>

#include "widgets/expandingWidget.h"
#include "widgets/courseTitleWidget.h"
#include "widgets/courseStatsWidget.h"

#include "pages/rootPage.h"

RootPage::RootPage(QWidget *parent)
    : QWidget(parent)
{
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



    newCourseButton = new QPushButton("Add a new course");
    QFont buttonFont = newCourseButton->font();
    buttonFont.setPointSize(24);
    newCourseButton->setFont(buttonFont);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(newCourseButton);
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
}