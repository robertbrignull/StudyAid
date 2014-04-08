#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class QLineEdit;
class QComboBox;

class FactForm : public QWidget
{
    Q_OBJECT

public:
    FactForm(QWidget *parent = 0);

    void setData(Fact fact);
    Fact getData();



    Fact fact;
    QLineEdit *nameInput;
    QComboBox *typeInput;
};