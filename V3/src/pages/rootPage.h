#pragma once

#include <QWidget>

class QPushButton;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(QWidget *parent = 0);

private:
    QPushButton *newCourseButton;
};