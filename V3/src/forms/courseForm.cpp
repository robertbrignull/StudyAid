#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "forms/courseForm.h"

CourseForm::CourseForm(QWidget *parent)
    : QWidget(parent)
{
    course = Course();

    QHBoxLayout *layout = new QHBoxLayout(this);

    nameInput = new QLineEdit();

    layout->addStretch(1);
    layout->addWidget(new QLabel("Name: "));
    layout->addWidget(nameInput);
    layout->addStretch(1);
}

void CourseForm::setData(Course course)
{
    this->course = course;

    nameInput->setText(QString::fromStdString(course.name));
}

Course CourseForm::getData()
{
    course.name = nameInput->text().toStdString();

    return course;
}