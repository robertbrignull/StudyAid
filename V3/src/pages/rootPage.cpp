#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>

#include "widgets/expandingWidget.h"

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



    layout->addWidget(new ExpandingWidget(new QLabel("Head"), new QLabel("Body")));
    layout->addWidget(new ExpandingWidget(new QLabel("Head"), new QLabel("Body")));
    layout->addWidget(new ExpandingWidget(new QLabel("Head"), new QLabel("Body")));



    layout->addStretch(1);
}