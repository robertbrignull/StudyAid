#include <iostream>

#include <QVBoxLayout>
#include <QLabel>

#include "database/methods.h"
#include "widgets/expandingFactWidget.h"
#include "widgets/sectionWidget.h"

#include "widgets/courseWidget.h"

CourseWidget::CourseWidget(int id, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 11);

    std::vector<Fact> facts = findChildFacts(id);

    for (size_t i = 0; i < facts.size(); ++i) {
        if (facts[i].type == "Section") {
            SectionWidget *sectionWidget = new SectionWidget(facts[i].id, facts[i].name);
            layout->addWidget(sectionWidget);

            connect(sectionWidget, &SectionWidget::viewButtonClicked, [=](int id){
                emit viewButtonClicked(id);
            });
        }
        else {
            ExpandingFactWidget *factWidget = new ExpandingFactWidget(facts[i].id, facts[i].name);
            layout->addWidget(factWidget);

            connect(factWidget, &ExpandingFactWidget::viewButtonClicked, [=](int id){
                emit viewButtonClicked(id);
            });
        }
    }
}