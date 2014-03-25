#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "forms/courseForm.h"

CourseForm::CourseForm(QWidget *parent)
    : Form(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    nameInput = new QLineEdit();

    layout->addStretch(1);
    layout->addWidget(new QLabel("Name: "));
    layout->addWidget(nameInput);
    layout->addStretch(1);
}

void CourseForm::setData(std::map<QString, QString> data)
{
    nameInput->setText(data[QString("name")]);
}

std::map<QString, QString> CourseForm::getData()
{
    std::map<QString, QString> data;

    data.insert(std::pair<QString, QString>(QString("name"), nameInput->text()));

    return data;
}