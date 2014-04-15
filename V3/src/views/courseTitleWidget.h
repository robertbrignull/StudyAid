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
    Model *model;

    int radius;
    QColor headColor, borderColor;

    QLabel *courseNameLabel;
    ImageButton *viewCourseButton;

    Course moveCourse;
    ImageButton *moveButton, *moveAboveButton, *moveBelowButton;

signals:
    void viewButtonClicked(Course course);

    void moveButtonClicked(Course course);
    void moveCompleted();

public slots:
    void viewButtonClickedSlot();

    void moveButtonClickedSlot();
    void moveAboveButtonClickedSlot();
    void moveBelowButtonClickedSlot();

    void activateMoveMode(Course course);
    void deactivateMoveMode();

    void courseEditedSlot(Course course);
};