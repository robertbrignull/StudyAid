#pragma once

#include <iostream>

#include "database/structures.h"
#include "forms/form.h"

class QLineEdit;

class CourseForm : public Form
{
    Q_OBJECT

public:
    CourseForm(QWidget *parent = 0);

    void clear();

    bool isValid();

    void setData(Course course);
    Course getData();



    Course course;
    QLineEdit *nameInput;
};