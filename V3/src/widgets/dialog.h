#pragma once

#include <iostream>
#include <map>

#include <QDialog>
#include <QString>

class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent, QWidget *body, std::string topText, std::string confirmButtonText, std::string cancelButtonText);



    QPushButton *cancelButton;
    QPushButton *confirmButton;

signals:
    void completed();
    void cancelled();
};