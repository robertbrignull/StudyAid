#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "forms/courseForm.h"

CourseForm::CourseForm(QWidget *parent)
    : Form(parent)
{
    course = Course();

    QHBoxLayout *layout = new QHBoxLayout(this);

    nameInput = new QLineEdit();

    layout->addStretch(1);
    layout->addWidget(new QLabel("Name: "));
    layout->addWidget(nameInput);
    layout->addStretch(1);

    connect(nameInput, SIGNAL(textChanged(QString)), this, SLOT(checkValidity()));
}

void CourseForm::clear()
{
    nameInput->setText("");
    currentlyValid = isValid();
}

bool CourseForm::isValid()
{
    return (nameInput->text() != "");
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