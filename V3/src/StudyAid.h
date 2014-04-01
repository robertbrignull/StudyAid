#pragma once

#include <QWidget>

class Model;

class StudyAid : public QWidget
{
    Q_OBJECT

public:
    StudyAid(QWidget *parent = 0);
    ~StudyAid();

private:
    Model *model;
};