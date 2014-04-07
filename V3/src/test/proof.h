#pragma once

#include <QObject>

class StudyAid;

class ProofTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void test_addProof();
    void test_addProof_multiple();

    void test_editProof();
    void test_editProof_body();

    void test_deleteProof_all();
    void test_deleteProof_one();

private:
    StudyAid *window;
};