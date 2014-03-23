#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>

#include "widgets/courseTitleWidget.h"

CourseTitleWidget::CourseTitleWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    QLabel *label = new QLabel("Linear Algebra");
    label->setWordWrap(true);

    QFont font = label->font();
    font.setPointSize(24);
    label->setFont(font);

    layout->addWidget(label);
    layout->addStretch(1);
    layout->addWidget(new QPushButton("X"));
    layout->addWidget(new QPushButton("->"));

    setMinimumWidth(600);
    setMaximumWidth(1000);
}