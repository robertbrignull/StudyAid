#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "widgets/courseStatsWidget.h"

CourseStatsWidget::CourseStatsWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    QLabel *label = new QLabel("Fusce molestie, libero nec pellentesque porta, purus massa feugiat leo, a faucibus enim ante pharetra felis. In tincidunt elit nec ligula auctor eleifend. Sed eu diam at ligula facilisis feugiat. Fusce vel vestibulum velit. In hac habitasse platea dictumst. Curabitur ornare interdum neque et semper. Proin odio nulla, accumsan ac enim in, dictum tempus turpis. Suspendisse eu enim nec massa aliquet convallis.");
    label->setWordWrap(true);

    layout->addWidget(label);

    setMaximumWidth(1000);
}