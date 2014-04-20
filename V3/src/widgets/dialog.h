#pragma once

#include <iostream>
#include <map>

#include <QDialog>
#include <QString>

class Form;
class QPushButton;
class QShowEvent;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent, Form *form, std::string topText, std::string confirmButtonText, std::string cancelButtonText);

    void showEvent(QShowEvent *e);



    Form *form;

    QPushButton *cancelButton;
    QPushButton *confirmButton;

public slots:
    void formValid();
    void formInvalid();
};