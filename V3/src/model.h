#pragma once

#include <QObject>

#include "database/structures.h"

class ModelSignaller : public QObject
{
    Q_OBJECT

signals:
    void courseAdded(Course course);
    void courseEdited(Course course);
    void courseOrderingEdited(Course course);
    void courseDeleted(int id);

    void factAdded(Fact fact);
    void factEdited(Fact fact);
    void factOrderingEdited(Fact fact);
    void factRendered(Fact fact, bool success);
    void factDeleted(int id);

    void proofAdded(Proof proof);
    void proofEdited(Proof proof);
    void proofOrderingEdited(Proof proof);
    void proofRendered(Proof proof, bool success);
    void proofDeleted(int id);

public slots:
    Course addCourse(std::string name);
    void editCourse(Course course);
    void editCourseOrdering(Course course);
    void deleteCourse(int id);

    Fact addFact(int parent, std::string name, std::string type);
    void editFact(Fact fact);
    void editFactOrdering(Fact fact);
    void renderFact(Fact fact);
    void deleteFact(int id);

    Proof addProof(int fact, std::string name);
    void editProof(Proof proof);
    void editProofOrdering(Proof proof);
    void renderProof(Proof proof);
    void deleteProof(int id);
};

class Model : public QObject
{
    Q_OBJECT

public:
    Model(ModelSignaller *modelSignaller);

    ModelSignaller *getModelSignaller();

    bool isCourseSelected();
    Course getCourseSelected();

    bool isFactSelected();
    Fact getFactSelected();

    bool isProofSelected();
    Proof getProofSelected();

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
    void factRendered(Fact fact, bool success);
    void factDeleted(int id);

    void proofSelectedChanged(Proof proof);
    void proofAdded(Proof proof);
    void proofEdited(Proof proof);
    void proofOrderingEdited(Proof proof);
    void proofRendered(Proof proof, bool success);
    void proofDeleted(int id);

public slots:
    void setCourseSelected(Course course);
    Course addCourse(std::string name);
    void editCourse(Course course);
    void editCourseOrdering(Course course);
    void deleteCourse(int id);

    void setFactSelected(Fact fact);
    Fact addFact(int parent, std::string name, std::string type);
    void editFact(Fact fact);
    void editFactOrdering(Fact fact);
    void renderFact(Fact fact);
    void deleteFact(int id);

    void setProofSelected(Proof proof);
    Proof addProof(int fact, std::string name);
    void editProof(Proof proof);
    void editProofOrdering(Proof proof);
    void renderProof(Proof proof);
    void deleteProof(int id);

    void courseEditedSlot(Course course);
    void courseOrderingEditedSlot(Course course);

    void factEditedSlot(Fact fact);
    void factOrderingEditedSlot(Fact fact);

    void proofEditedSlot(Proof proof);
    void proofOrderingEditedSlot(Proof proof);

private:
    ModelSignaller *modelSignaller;

    bool courseSelected, factSelected, proofSelected;

    Course course;
    Fact fact;
    Proof proof;
};