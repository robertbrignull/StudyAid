#pragma once

#include <QWidget>

class CourseWidget : public QWidget
{
    Q_OBJECT

public:
    CourseWidget(int id, QWidget *parent = 0);

signals:
    void viewButtonClicked(int id);
};