#pragma once

#include <iostream>

#include <QDialog>
#include <QString>

class QPushButton;

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    DeleteDialog(QWidget *parent, std::string text);



    QPushButton *cancelButton;
    QPushButton *acceptButton;

signals:
    void accepted();
    void cancelled();
};