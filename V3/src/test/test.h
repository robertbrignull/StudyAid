#pragma once

#include <QObject>

class StudyAid;

class Test : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addCourse();
    void test_editCourse();

private:
    void addCourse(const char *name);
    void editCourse(const char *name);



    StudyAid *window;
};