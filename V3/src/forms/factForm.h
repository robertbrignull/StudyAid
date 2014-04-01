#pragma once

#include <iostream>
#include <map>

#include "forms/form.h"

class QLineEdit;
class QComboBox;

class FactForm : public Form
{
    Q_OBJECT

public:
    FactForm(QWidget *parent = 0);

    void setData(std::map<std::string, std::string> data);
    std::map<std::string, std::string> getData();

private:
    QLineEdit *nameInput;
    QComboBox *typeInput;
};