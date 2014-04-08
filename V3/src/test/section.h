#pragma once

#include <QObject>

class StudyAid;

class SectionTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addSection_toRoot();
    void test_addSection_toSection();

    void test_selectSection();

    void test_editSection();

    void test_deleteSection_empty();
    void test_deleteSection_notEmpty();

private:
    StudyAid *window;
};