#include <iostream>

#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

#include "database/methods.h"
#include "widgets/expandingFactWidget.h"

#include "widgets/sectionWidget.h"

SectionWidget::SectionWidget(int id, std::string title, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(11, 0, 0, 11);

    layout->addWidget(new QLabel(QString::fromStdString(title)));

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

void SectionWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush(QColor(QColor(66, 139, 202))), 2));

    painter.drawLine(1, 1, 31, 1);
    painter.drawLine(1, 1, 1, size().height()-1);
    painter.drawLine(1, size().height()-1, 31, size().height()-1);
}