#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class QLineEdit;

class ProofForm : public QWidget
{
    Q_OBJECT

public:
    ProofForm(QWidget *parent = 0);

    void setData(Proof proof);
    Proof getData();



    Proof proof;
    QLineEdit *nameInput;
};