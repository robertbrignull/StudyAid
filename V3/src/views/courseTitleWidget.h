#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>

#include "database/structures.h"

class CourseTitleWidget : public QWidget
{
    Q_OBJECT

public:
    CourseTitleWidget(Course course, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);



    Course course;
    int radius;
    QColor headColor, borderColor;

signals:
    void viewButtonClicked(Course course);

public slots:
    void viewButtonClickedSlot();
};