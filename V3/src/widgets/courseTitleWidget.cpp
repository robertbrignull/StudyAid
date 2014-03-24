#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QPalette>

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

    QPalette pal = label->palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    label->setPalette(pal);

    layout->addWidget(label);
    layout->addStretch(1);
    layout->addWidget(new QPushButton("->"));
}