#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QPainter>
#include <QLabel>

#include "model.h"
#include "widgets/imageButton.h"
#include "widgets/resizableStackedWidget.h"
#include "database/methods.h"

#include "views/courseTitleWidget.h"

CourseTitleWidget::CourseTitleWidget(Course course, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->course = course;
    this->model = model;
    this->pageStack = pageStack;

    headColor = QColor(66, 139, 202);
    borderColor = QColor(66, 139, 202);
    radius = 4;



    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 8, 16, 8);

    courseNameLabel = new QLabel(QString::fromStdString(course.name));
    courseNameLabel->setWordWrap(true);

    QFont font = courseNameLabel->font();
    font.setPointSize(18);
    courseNameLabel->setFont(font);

    QPalette pal = courseNameLabel->palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    courseNameLabel->setPalette(pal);

    viewCourseButton = new ImageButton(QPixmap(":/images/arrow_right_white.png"), QSize(24, 24));

    moveButton = new ImageButton(QPixmap(":/images/move_white.png"), QSize(24, 24));
    moveAboveButton = new ImageButton(QPixmap(":/images/arrow_up_white.png"), QSize(24, 24));
    moveBelowButton = new ImageButton(QPixmap(":/images/arrow_down_white.png"), QSize(24, 24));

    layout->addWidget(courseNameLabel);
    layout->addWidget(moveBelowButton);
    layout->addWidget(moveAboveButton);
    layout->addWidget(moveButton);
    layout->addWidget(viewCourseButton);

    deactivateMoveMode();



    connect(viewCourseButton, SIGNAL(clicked()), this, SLOT(viewButtonClickedSlot()));

    connect(moveButton, SIGNAL(clicked()), this, SLOT(moveButtonClickedSlot()));
    connect(moveAboveButton, SIGNAL(clicked()), this, SLOT(moveAboveButtonClickedSlot()));
    connect(moveBelowButton, SIGNAL(clicked()), this, SLOT(moveBelowButtonClickedSlot()));

    connect(model, SIGNAL(courseEdited(Course)), this, SLOT(courseEditedSlot(Course)));
}

void CourseTitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QBrush(borderColor), 1));
    painter.setBrush(QBrush(headColor));
    painter.drawRoundedRect(1, 1, size().width()-2, size().height()-2, radius, radius);
}

void CourseTitleWidget::viewButtonClickedSlot()
{
    model->setCourseSelected(course);
    pageStack->setCurrentIndex(1);
}

void CourseTitleWidget::moveButtonClickedSlot()
{
    if (inMoveMode) {
        emit moveCompleted();
    }
    else {
        emit moveButtonClicked(course);
    }
}

void CourseTitleWidget::moveAboveButtonClickedSlot()
{
    moveCourse.ordering = course.ordering;

    model->editCourseOrdering(moveCourse);

    emit moveCompleted();
}

void CourseTitleWidget::moveBelowButtonClickedSlot()
{
    moveCourse.ordering = course.ordering + 1;

    model->editCourseOrdering(moveCourse);

    emit moveCompleted();
}

void CourseTitleWidget::activateMoveMode(Course course)
{
    inMoveMode = true;
    moveCourse = course;

    viewCourseButton->hide();

    if (course.id == this->course.id) {
        moveButton->show();
        moveAboveButton->hide();
        moveBelowButton->hide();
    }
    else {
        moveButton->hide();
        moveAboveButton->show();
        moveBelowButton->show();
    }
}

void CourseTitleWidget::deactivateMoveMode()
{
    inMoveMode = false;

    viewCourseButton->show();
    moveButton->show();
    moveAboveButton->hide();
    moveBelowButton->hide();
}

void CourseTitleWidget::courseEditedSlot(Course course)
{
    if (course.id == this->course.id) {
        this->course = course;

        courseNameLabel->setText(QString::fromStdString(course.name));
    }
}