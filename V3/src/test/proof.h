#pragma once

#include <QObject>

class ModelSignaller;
class StudyAid;

class ProofTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addProof_form();
    void test_addProof();
    void test_addProof_multiple();
    void test_addProof_nameEmpty();

    void test_editProof_form();
    void test_editProof();
    void test_editProof_body();
    void test_editProof_nameEmpty();

    void test_editProofOrdering_moveMode();
    void test_editProofOrdering_moveAbove();
    void test_editProofOrdering_moveBelow();
    void test_editProofOrdering_moveBetween();

    void test_deleteProof_all();
    void test_deleteProof_one();

    void test_viewProof_bodyEmpty();
    void test_viewProof_bodyNotEmpty();

private:
    ModelSignaller *modelSignaller;
    StudyAid *window;
};