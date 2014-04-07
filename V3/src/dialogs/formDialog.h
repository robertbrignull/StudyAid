#pragma once

#include <iostream>
#include <map>

#include <QDialog>
#include <QString>

#include "forms/form.h"

class QPushButton;

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    FormDialog(QWidget *parent, Form *form, std::string topText, std::string buttonText);



    QPushButton *cancelButton;
    QPushButton *completeButton;

signals:
    void completed(std::map<std::string, std::string> data);
    void cancelled();
};