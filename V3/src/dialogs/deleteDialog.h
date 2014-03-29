#pragma once

#include <iostream>

#include <QDialog>
#include <QString>

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    DeleteDialog(QWidget *parent, std::string text);

signals:
    void accepted();
    void cancelled();
};