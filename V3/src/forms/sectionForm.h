#pragma once

#include <iostream>

#include <QWidget>

#include "database/structures.h"
#include "forms/form.h"

class QLineEdit;

class SectionForm : public Form
{
    Q_OBJECT

public:
    SectionForm(QWidget *parent = 0);

    void clear();

    bool isValid();

    void setData(Fact section);
    Fact getData();



    Fact section;
    QLineEdit *nameInput;
};