#pragma once

#include <iostream>
#include <map>

#include <QDialog>
#include <QString>

#include "forms/form.h"

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    FormDialog(QWidget *parent, Form *form, std::string topText, std::string buttonText);

signals:
    void completed(std::map<std::string, std::string> data);
    void cancelled();
};