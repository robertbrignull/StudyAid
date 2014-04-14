#pragma once

#include <QObject>

#include "database/structures.h"

class Model : public QObject
{
    Q_OBJECT

public:
    Model();

    bool isCourseSelected();
    Course getCourseSelected();
    void setCourseSelected(Course course);
    void addCourse(Course course);
    void editCourse(Course course);
    void editCourseOrdering(Course course);
    void deleteCourse(int id);

    bool isFactSelected();
    Fact getFactSelected();
    void setFactSelected(Fact fact);
    void addFact(Fact fact);
    void editFact(Fact fact);
    void editFactOrdering(Fact fact);
    void deleteFact(int id);

    bool isProofSelected();
    Proof getProofSelected();
    void setProofSelected(Proof proof);
    void addProof(Proof proof);
    void editProof(Proof proof);
    void editProofOrdering(Proof proof);
    void deleteProof(int id);

signals:
    void courseSelectedChanged(Course course);
    void courseAdded(Course course);
    void courseEdited(Course course);
    void courseOrderingEdited(Course course);
    void courseDeleted(int id);

    void factSelectedChanged(Fact fact);
    void factAdded(Fact fact);
    void factEdited(Fact fact);
    void factOrderingEdited(Fact fact);
    void factDeleted(int id);

    void proofSelectedChanged(Proof proof);
    void proofAdded(Proof proof);
    void proofEdited(Proof proof);
    void proofOrderingEdited(Proof proof);
    void proofDeleted(int id);

private:
    bool courseSelected, factSelected, proofSelected;

    Course course;
    Fact fact;
    Proof proof;
};