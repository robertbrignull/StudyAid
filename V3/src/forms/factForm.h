#pragma once

#include <iostream>

#include <QWidget>

#include "database/structures.h"
#include "forms/form.h"

class QLineEdit;
class QComboBox;

class FactForm : public Form
{
    Q_OBJECT

public:
    FactForm(QWidget *parent = 0);

    void clear();

    bool isValid();

    void setData(Fact fact);
    Fact getData();



    Fact fact;
    QLineEdit *nameInput;
    QComboBox *typeInput;
};