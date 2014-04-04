#pragma once

#include <QObject>

class StudyAid;

class FactTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addFact();
    void test_editFact();
    void test_deleteFact();

private:
    StudyAid *window;
};