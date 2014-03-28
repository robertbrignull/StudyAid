#pragma once

#include "map"

#include "forms/form.h"

class QLineEdit;

class ProofForm : public Form
{
    Q_OBJECT

public:
    ProofForm(QWidget *parent = 0);

    void setData(std::map<QString, QString> data);
    std::map<QString, QString> getData();

private:
    QLineEdit *nameInput;
};