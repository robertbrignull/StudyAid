#include <iostream>

#include <QVBoxLayout>
#include <QLabel>

#include "widgets/expandingFactWidget.h"
#include "widgets/sectionWidget.h"

#include "widgets/courseWidget.h"

CourseWidget::CourseWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    ExpandingFactWidget *fact = new ExpandingFactWidget("Independent fact");
    SectionWidget *section1 = new SectionWidget(1, "Section 1");
    SectionWidget *section2 = new SectionWidget(3, "Section 2");

    layout->addWidget(fact);
    layout->addWidget(section1);
    layout->addWidget(section2);

    connect(fact, &ExpandingFactWidget::viewButtonClicked, [=](){
        emit viewButtonClicked(0);
    });

    connect(section1, &SectionWidget::viewButtonClicked, [=](int id){
        emit viewButtonClicked(id);
    });

    connect(section2, &SectionWidget::viewButtonClicked, [=](int id){
        emit viewButtonClicked(id);
    });
}