#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QSplitter>
#include <QScrollArea>

#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/courseWidget.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/courseForm.h"

#include "pages/coursePage.h"

CoursePage::CoursePage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    CourseForm *courseEditForm = new CourseForm();
    FormDialog *courseEditDialog = new FormDialog(this, courseEditForm, QString("Edit the course..."), QString("Change"));

    DeleteDialog *courseDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this course?");




    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    QWidget *crumbWidget = new QWidget();
    crumbWidget->setFixedWidth(700);
    QHBoxLayout *crumbLayout = new QHBoxLayout(crumbWidget);
    crumbLayout->setContentsMargins(0, 0, 0, 0);

    ClickableQLabel *coursesLabel = new ClickableQLabel("Courses");
    QLabel *currentFactLabel = new QLabel(" / Linear Algebra");

    QFont font = coursesLabel->font();
    font.setPointSize(14);
    coursesLabel->setFont(font);
    currentFactLabel->setFont(font);

    QPalette palette = coursesLabel->palette();

    palette.setColor(QPalette::WindowText, Qt::blue);
    palette.setColor(QPalette::Text, Qt::blue);
    coursesLabel->setPalette(palette);

    palette.setColor(QPalette::WindowText, Qt::gray);
    palette.setColor(QPalette::Text, Qt::gray);
    currentFactLabel->setPalette(palette);

    crumbLayout->addWidget(coursesLabel);
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
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 1));
    outerLayout->addSpacing(20);



    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    QScrollArea *pickerScrollArea = new QScrollArea();
    pickerScrollArea->setWidgetResizable(true);
    pickerScrollArea->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(pickerScrollArea);

    QWidget *pickerScrollWidget = new QWidget();
    QVBoxLayout *pickerScrollLayout = new QVBoxLayout(pickerScrollWidget);
    pickerScrollArea->setWidget(pickerScrollWidget);

    pickerScrollLayout->addWidget(new QLabel("Section picker"));
    pickerScrollLayout->addStretch(1);



    QScrollArea *courseScrollArea = new QScrollArea();
    courseScrollArea->setWidgetResizable(true);
    courseScrollArea->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(courseScrollArea);

    QWidget *courseScrollWidget = new QWidget();
    QVBoxLayout *courseScrollLayout = new QVBoxLayout(courseScrollWidget);
    courseScrollArea->setWidget(courseScrollWidget);

    CourseWidget *courseWidget = new CourseWidget();
    courseScrollLayout->addWidget(courseWidget);
    courseScrollLayout->addStretch(1);



    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);



    connect(coursesLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(0);
    });

    connect(editCourseButton, &ImageButton::clicked, [=](){
        std::map<QString, QString> data;
        data.insert(std::pair<QString, QString>(QString("name"), QString("Linear Algebra")));
        courseEditForm->setData(data);
        courseEditDialog->show();
    });

    connect(courseEditDialog, &FormDialog::cancelled, [=](){
        courseEditDialog->close();
    });

    connect(courseEditDialog, &FormDialog::completed, [=](std::map<QString, QString> data){
        std::cout << "Change course name to: " << data[QString("name")].toStdString() << std::endl;
        courseEditDialog->close();
    });

    connect(deleteCourseButton, &ImageButton::clicked, [=](){
        courseDeleteDialog->show();
    });

    connect(courseDeleteDialog, &DeleteDialog::accepted, [=](){
        std::cout << "Deleted course" << std::endl;
        courseDeleteDialog->close();
        pageStack->setCurrentIndex(0);
    });

    connect(courseDeleteDialog, &DeleteDialog::cancelled, [=](){
        courseDeleteDialog->close();
    });

    connect(courseWidget, &CourseWidget::viewButtonClicked, [=](int id){
        std::cout << "Fact view button clicked: " << id << std::endl;
    });
}