#include <iostream>

#include <map>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>
#include <QScrollArea>
#include <QString>

#include "widgets/courseTitleWidget.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/imageButton.h"
#include "dialogs/formDialog.h"
#include "forms/courseForm.h"

#include "pages/rootPage.h"

RootPage::RootPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    FormDialog *courseAddDialog = new FormDialog(this, new CourseForm(), QString("Add a new course..."), QString("Add"));



    QHBoxLayout *outerLayout = new QHBoxLayout(this);

    QWidget *innerWidget = new QWidget();
    QVBoxLayout *innerLayout = new QVBoxLayout(innerWidget);
    innerWidget->setFixedWidth(700);

    outerLayout->addStretch(1);
    outerLayout->addWidget(innerWidget, 1);
    outerLayout->addStretch(1);



    QLabel *titleLabel = new QLabel("Study Aid");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(64);
    titleFont.setBold(true);
    titleFont.setFamily("Helvetica");
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    innerLayout->addWidget(titleLabel);



    QLabel *coursesLabel = new QLabel("Courses...");
    QFont coursesFont = coursesLabel->font();
    coursesFont.setPointSize(38);
    coursesLabel->setFont(coursesFont);

    ImageButton *newCourseButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(32, 32));
    QVBoxLayout *newCourseVLayout = new QVBoxLayout();
    newCourseVLayout->addSpacing(16);
    newCourseVLayout->addWidget(newCourseButton);

    QHBoxLayout *newCourseHLayout = new QHBoxLayout();
    newCourseHLayout->addSpacing(10);
    newCourseHLayout->addWidget(coursesLabel);
    newCourseHLayout->addStretch(1);
    newCourseHLayout->addLayout(newCourseVLayout);
    newCourseHLayout->addSpacing(22);

    innerLayout->addLayout(newCourseHLayout);



    innerLayout->addSpacing(20);
    innerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 1));
    innerLayout->addSpacing(20);



    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    
    scrollArea->setWidget(scrollWidget);
    innerLayout->addWidget(scrollArea);

    CourseTitleWidget *courseTitleWidget1 = new CourseTitleWidget(0, "Part A: Linear Algebra");
    connect(courseTitleWidget1, &CourseTitleWidget::viewButtonClicked, [=](){ pageStack->setCurrentIndex(1); });
    scrollLayout->addWidget(courseTitleWidget1);

    CourseTitleWidget *courseTitleWidget2 = new CourseTitleWidget(0, "Part A: Complex Analysis");
    connect(courseTitleWidget2, &CourseTitleWidget::viewButtonClicked, [=](){ pageStack->setCurrentIndex(1); });
    scrollLayout->addWidget(courseTitleWidget2);

    CourseTitleWidget *courseTitleWidget3 = new CourseTitleWidget(0, "Part B: Set Theory");
    connect(courseTitleWidget3, &CourseTitleWidget::viewButtonClicked, [=](){ pageStack->setCurrentIndex(1); });
    scrollLayout->addWidget(courseTitleWidget3);

    scrollLayout->addStretch(1);



    connect(newCourseButton, &QPushButton::clicked, [=](){
        courseAddDialog->show();
    });

    connect(courseAddDialog, &FormDialog::completed, [=](std::map<QString, QString> data){
        std::cout << "Added course: " << data[QString("name")].toStdString() << std::endl;
        courseAddDialog->close();
        pageStack->setCurrentIndex(1);
    });

    connect(courseAddDialog, &FormDialog::cancelled, [=](){
        courseAddDialog->close();
    });
}