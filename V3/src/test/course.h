#pragma once

#include <QObject>

class StudyAid;

class CourseTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addCourse();
    void test_editCourse();
    void test_deleteCourse();

private:
    void addCourse(const char *name);
    void editCurrentCourse(const char *name);
    void deleteCurrentCourse();



    StudyAid *window;
};