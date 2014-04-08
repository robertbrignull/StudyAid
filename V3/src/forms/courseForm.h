#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class QLineEdit;

class CourseForm : public QWidget
{
    Q_OBJECT

public:
    CourseForm(QWidget *parent = 0);

    void setData(Course course);
    Course getData();



    Course course;
    QLineEdit *nameInput;
};