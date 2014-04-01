#pragma once

#include <iostream>
#include <map>

#include <QWidget>

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = 0) : QWidget(parent) { }

    virtual void setData(std::map<std::string, std::string> data) = 0;
    virtual std::map<std::string, std::string> getData() = 0;
};