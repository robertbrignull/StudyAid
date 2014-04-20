#pragma once

#include <iostream>

#include <QWidget>

class QLineEdit;
class QComboBox;

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = 0);

    virtual void clear() = 0;

    virtual bool isValid() = 0;


    bool currentlyValid;

signals:
    void valid();
    void invalid();
 
public slots:
    void checkValidity();
};