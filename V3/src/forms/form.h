#pragma once

#include <QWidget>

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = 0) : QWidget(parent) { }

    virtual void setData(std::map<QString, QString> data) = 0;
    virtual std::map<QString, QString> getData() = 0;
};