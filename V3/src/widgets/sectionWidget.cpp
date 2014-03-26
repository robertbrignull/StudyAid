#include <iostream>

#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

#include "widgets/expandingFactWidget.h"

#include "widgets/sectionWidget.h"

SectionWidget::SectionWidget(int id, QString title, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(title));

    ExpandingFactWidget *fact1 = new ExpandingFactWidget(id, "Dependent fact 1");
    ExpandingFactWidget *fact2 = new ExpandingFactWidget(id+1, "Dependent fact 2");

    layout->addWidget(fact1);
    layout->addWidget(fact2);

    connect(fact1, &ExpandingFactWidget::viewButtonClicked, [=](){
        emit viewButtonClicked(id);
    });

    connect(fact2, &ExpandingFactWidget::viewButtonClicked, [=](){
        emit viewButtonClicked(id+1);
    });
}

void SectionWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush(QColor(QColor(66, 139, 202))), 2));

    painter.drawLine(1, 1, 31, 1);
    painter.drawLine(1, 1, 1, size().height()-1);
    painter.drawLine(1, size().height()-1, 31, size().height()-1);
}