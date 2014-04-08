#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class QLineEdit;

class SectionForm : public QWidget
{
    Q_OBJECT

public:
    SectionForm(QWidget *parent = 0);

    void setData(Fact section);
    Fact getData();



    Fact section;
    QLineEdit *nameInput;
};