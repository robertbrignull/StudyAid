#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"

#include "pages/coursePage.h"

CoursePage::CoursePage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->pageStack = pageStack;



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topWidget->setFixedWidth(700);

    QLabel *courseLabel = new QLabel("Linear Algebra");
    QFont courseFont = courseLabel->font();
    courseFont.setPointSize(38);
    courseLabel->setFont(courseFont);

    ImageButton *newFactButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(32, 32));
    QVBoxLayout *newFactVLayout = new QVBoxLayout();
    newFactVLayout->addSpacing(16);
    newFactVLayout->addWidget(newFactButton);

    topLayout->addSpacing(10);
    topLayout->addWidget(courseLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(newFactVLayout);
    topLayout->addSpacing(22);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);


    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 1));
    outerLayout->addSpacing(20);



    outerLayout->addStretch(1);
}