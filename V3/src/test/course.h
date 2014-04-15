#pragma once

#include <QObject>

class StudyAid;

class CourseTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addCourse_one();
    void test_addCourse_multiple();

    void test_editCourse();

    void test_editCourseOrdering_moveMode();
    void test_editCourseOrdering_moveAbove();
    void test_editCourseOrdering_moveBelow();
    void test_editCourseOrdering_moveBetween();

    void test_deleteCourse_all();
    void test_deleteCourse_one();

private:
    StudyAid *window;
};