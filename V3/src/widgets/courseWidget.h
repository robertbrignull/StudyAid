#pragma once

#include <QWidget>

class CourseWidget : public QWidget
{
    Q_OBJECT

public:
    CourseWidget(QWidget *parent = 0);

signals:
    void viewButtonClicked(int id);
};