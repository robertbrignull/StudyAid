#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QPainter>
#include <QLabel>

#include "model.h"
#include "widgets/imageButton.h"

#include "views/courseTitleWidget.h"

CourseTitleWidget::CourseTitleWidget(Course course, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->course = course;

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

    layout->addWidget(courseNameLabel);
    layout->addWidget(viewCourseButton);



    connect(viewCourseButton, SIGNAL(clicked()), this, SLOT(viewButtonClickedSlot()));

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
    emit viewButtonClicked(course);
}

void CourseTitleWidget::courseEditedSlot(Course course)
{
    if (course.id == this->course.id) {
        this->course = course;

        courseNameLabel->setText(QString::fromStdString(course.name));
    }
}