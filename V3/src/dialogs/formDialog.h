#pragma once

#include "map"

#include <QDialog>
#include <QString>

#include "forms/form.h"

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    FormDialog(QWidget *parent, Form *form, QString topText, QString buttonText);

signals:
    void completed(std::map<QString, QString> data);
    void cancelled();
};