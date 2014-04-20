#include <iostream>

#include "forms/form.h"

Form::Form(QWidget *parent)
    : QWidget(parent)
{

}

void Form::checkValidity()
{
    if (currentlyValid && !isValid()) {
        currentlyValid = false;
        emit invalid();
    }
    else if (!currentlyValid && isValid()) {
        currentlyValid = true;
        emit valid();
    }
}