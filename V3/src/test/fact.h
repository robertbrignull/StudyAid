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
    void test_addFact_canHaveProof();
    void test_addFact_canNotHaveProof();
    void test_editFact();
    void test_editFact_canHaveProof();
    void test_editFact_canNotHaveProof();
    void test_deleteFact();

private:
    StudyAid *window;
};