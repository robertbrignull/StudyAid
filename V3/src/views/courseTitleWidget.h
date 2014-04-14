#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>

#include "database/structures.h"

class Model;
class QLabel;
class ImageButton;

class CourseTitleWidget : public QWidget
{
    Q_OBJECT

public:
    CourseTitleWidget(Course course, Model *model, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);



    Course course;

    int radius;
    QColor headColor, borderColor;

    QLabel *courseNameLabel;
    ImageButton *viewCourseButton;

signals:
    void viewButtonClicked(Course course);

public slots:
    void viewButtonClickedSlot();

    void courseEditedSlot(Course course);
};