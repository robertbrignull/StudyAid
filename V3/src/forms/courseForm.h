#pragma once

#include <iostream>
#include <map>

#include "forms/form.h"

class QLineEdit;

class CourseForm : public Form
{
    Q_OBJECT

public:
    CourseForm(QWidget *parent = 0);

    void setData(std::map<std::string, std::string> data);
    std::map<std::string, std::string> getData();



    QLineEdit *nameInput;
};