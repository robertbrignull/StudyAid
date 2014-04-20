#pragma once

#include <iostream>

#include <QWidget>

#include "database/structures.h"
#include "forms/form.h"

class QLineEdit;

class ProofForm : public Form
{
    Q_OBJECT

public:
    ProofForm(QWidget *parent = 0);

    void clear();

    bool isValid();

    void setData(Proof proof);
    Proof getData();



    Proof proof;
    QLineEdit *nameInput;
};