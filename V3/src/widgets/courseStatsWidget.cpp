#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "widgets/courseStatsWidget.h"

CourseStatsWidget::CourseStatsWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    QLabel *label = new QLabel("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam egestas fringilla mattis. Suspendisse feugiat sit amet lectus ac ultricies. Integer feugiat enim sit amet nisi tincidunt, quis blandit purus adipiscing. Sed scelerisque viverra metus quis pharetra. In scelerisque scelerisque laoreet. Integer sed commodo dolor. Proin laoreet sit amet purus a pellentesque.");
    label->setWordWrap(true);

    layout->addWidget(label);
}