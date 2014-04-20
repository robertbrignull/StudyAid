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

    void test_editSection_form();
    void test_editSection();

    void test_editSectionOrdering_moveMode();
    void test_editSectionOrdering_moveAbove();
    void test_editSectionOrdering_moveBelow();
    void test_editSectionOrdering_moveBetween();

    void test_editSectionOrdering_factIntoSection();
    void test_editSectionOrdering_sectionIntoSection();
    void test_editSectionOrdering_factOutOfSection();
    void test_editSectionOrdering_sectionOutOfSection();

    void test_deleteSection_empty();
    void test_deleteSection_notEmpty();

private:
    StudyAid *window;
};