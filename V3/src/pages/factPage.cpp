#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QScrollArea>

#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/splitter.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/factForm.h"

#include "pages/factPage.h"

FactPage::FactPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    QWidget *crumbWidget = new QWidget();
    crumbWidget->setFixedWidth(700);
    QHBoxLayout *crumbLayout = new QHBoxLayout(crumbWidget);
    crumbLayout->setContentsMargins(0, 0, 0, 0);

    ClickableQLabel *coursesLabel = new ClickableQLabel("Courses");
    ClickableQLabel *factsLabel = new ClickableQLabel("Linear Algebra");
    QLabel *currentFactLabel = new QLabel(" / Vector Space");
    QLabel *sep1Label = new QLabel(" / ");

    QFont font = coursesLabel->font();
    font.setPointSize(14);
    coursesLabel->setFont(font);
    factsLabel->setFont(font);
    currentFactLabel->setFont(font);
    sep1Label->setFont(font);

    QPalette palette = coursesLabel->palette();

    palette.setColor(QPalette::WindowText, Qt::blue);
    palette.setColor(QPalette::Text, Qt::blue);
    coursesLabel->setPalette(palette);
    factsLabel->setPalette(palette);

    palette.setColor(QPalette::WindowText, Qt::gray);
    palette.setColor(QPalette::Text, Qt::gray);
    currentFactLabel->setPalette(palette);
    sep1Label->setPalette(palette);

    crumbLayout->addWidget(coursesLabel);
    crumbLayout->addWidget(sep1Label);
    crumbLayout->addWidget(factsLabel);
    crumbLayout->addWidget(currentFactLabel);
    crumbLayout->addStretch(1);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(crumbWidget);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *courseLabel = new QLabel("Linear Algebra");
    QFont courseFont = courseLabel->font();
    courseFont.setPointSize(38);
    courseLabel->setFont(courseFont);

    ImageButton *editCourseButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editCourseVLayout = new QVBoxLayout();
    editCourseVLayout->addSpacing(16);
    editCourseVLayout->addWidget(editCourseButton);

    ImageButton *deleteCourseButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteCourseVLayout = new QVBoxLayout();
    deleteCourseVLayout->addSpacing(16);
    deleteCourseVLayout->addWidget(deleteCourseButton);

    topLayout->addWidget(courseLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(editCourseVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteCourseVLayout);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);


    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    outerLayout->addSpacing(20);

    outerLayout->addStretch(1);



    connect(coursesLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(0);
    });

    connect(factsLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(1);
    });
}