#include <iostream>

#include "model.h"

//   #####  ######  #####  ##    ##    ##    ##      ##      ###### ######
//  ##   ##   ##   ##   ## ###   ##   ####   ##      ##      ##     ##   ##
//   ##       ##   ##      ####  ##  ##  ##  ##      ##      ##     ##   ##
//    ###     ##   ##      ## ## ## ##    ## ##      ##      ####   ######
//      ##    ##   ##  ### ##  #### ######## ##      ##      ##     ##  ##
//  ##   ##   ##   ##   ## ##   ### ##    ## ##      ##      ##     ##   ##
//   #####  ######  #####  ##    ## ##    ## ####### ####### ###### ##   ##

void ModelSignaller::addCourse(Course course)
{
    emit courseAdded(course);
}

void ModelSignaller::editCourse(Course course)
{
    emit courseEdited(course);
}

void ModelSignaller::editCourseOrdering(Course course)
{
    emit courseOrderingEdited(course);
}

void ModelSignaller::deleteCourse(int id)
{
    emit courseDeleted(id);
}

void ModelSignaller::addFact(Fact fact)
{
    emit factAdded(fact);
}

void ModelSignaller::editFact(Fact fact)
{
    emit factEdited(fact);
}

void ModelSignaller::editFactOrdering(Fact fact)
{
    emit factOrderingEdited(fact);
}

void ModelSignaller::deleteFact(int id)
{
    emit factDeleted(id);
}

void ModelSignaller::addProof(Proof proof)
{
    emit proofAdded(proof);
}

void ModelSignaller::editProof(Proof proof)
{
    emit proofEdited(proof);
}

void ModelSignaller::editProofOrdering(Proof proof)
{
    emit proofOrderingEdited(proof);
}

void ModelSignaller::deleteProof(int id)
{
    emit proofDeleted(id);
}



//  ##    ## ###### ###### ##          ##
//  ##    ##   ##   ##     ##          ##
//   ##  ##    ##   ##      ##   ##   ##
//   ##  ##    ##   ####    ##  ####  ##
//    ####     ##   ##       ####  ####
//    ####     ##   ##       ####  ####
//     ##    ###### ######    ##    ##

Model::Model(ModelSignaller *modelSignaller)
{
    this->modelSignaller = modelSignaller;

    courseSelected = factSelected = proofSelected = false;



    connect(modelSignaller, SIGNAL(courseAdded(Course)), this, SIGNAL(courseAdded(Course)));
    connect(modelSignaller, SIGNAL(courseEdited(Course)), this, SIGNAL(courseEdited(Course)));
    connect(modelSignaller, SIGNAL(courseOrderingEdited(Course)), this, SIGNAL(courseOrderingEdited(Course)));
    connect(modelSignaller, SIGNAL(courseDeleted(int)), this, SIGNAL(courseDeleted(int)));

    connect(modelSignaller, SIGNAL(factAdded(Fact)), this, SIGNAL(factAdded(Fact)));
    connect(modelSignaller, SIGNAL(factEdited(Fact)), this, SIGNAL(factEdited(Fact)));
    connect(modelSignaller, SIGNAL(factOrderingEdited(Fact)), this, SIGNAL(factOrderingEdited(Fact)));
    connect(modelSignaller, SIGNAL(factDeleted(int)), this, SIGNAL(factDeleted(int)));

    connect(modelSignaller, SIGNAL(proofAdded(Proof)), this, SIGNAL(proofAdded(Proof)));
    connect(modelSignaller, SIGNAL(proofEdited(Proof)), this, SIGNAL(proofEdited(Proof)));
    connect(modelSignaller, SIGNAL(proofOrderingEdited(Proof)), this, SIGNAL(proofOrderingEdited(Proof)));
    connect(modelSignaller, SIGNAL(proofDeleted(int)), this, SIGNAL(proofDeleted(int)));
}

ModelSignaller *Model::getModelSignaller()
{
    return modelSignaller;
}

bool Model::isCourseSelected()
{
    return courseSelected;
}

Course Model::getCourseSelected()
{
    return course;
}

void Model::setCourseSelected(Course course)
{
    courseSelected = true;
    this->course = course;
    emit courseSelectedChanged(course);
}

void Model::addCourse(Course course)
{
    modelSignaller->addCourse(course);
}

void Model::editCourse(Course course)
{
    if (course.id == this->course.id) {
        this->course = course;
    }

    modelSignaller->editCourse(course);
}

void Model::editCourseOrdering(Course course)
{
    if (course.id == this->course.id) {
        this->course = course;
    }

    modelSignaller->editCourseOrdering(course);
}

void Model::deleteCourse(int id)
{
    modelSignaller->deleteCourse(id);
}

bool Model::isFactSelected()
{
    return factSelected;
}

Fact Model::getFactSelected()
{
    return fact;
}

void Model::setFactSelected(Fact fact)
{
    factSelected = true;
    this->fact = fact;
    emit factSelectedChanged(fact);
}

void Model::addFact(Fact fact)
{
    modelSignaller->addFact(fact);
}

void Model::editFact(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
    }

    modelSignaller->editFact(fact);
}

void Model::editFactOrdering(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
    }

    modelSignaller->editFactOrdering(fact);
}

void Model::deleteFact(int id)
{
    modelSignaller->deleteFact(id);
}

bool Model::isProofSelected()
{
    return proofSelected;
}

Proof Model::getProofSelected()
{
    return proof;
}

void Model::setProofSelected(Proof proof)
{
    proofSelected = true;
    this->proof = proof;
    emit proofSelectedChanged(proof);
}

void Model::addProof(Proof proof)
{
    modelSignaller->addProof(proof);
}

void Model::editProof(Proof proof)
{
    if (proof.id == this->proof.id) {
        this->proof = proof;
    }

    modelSignaller->editProof(proof);
}

void Model::editProofOrdering(Proof proof)
{
    if (proof.id == this->proof.id) {
        this->proof = proof;
    }

    modelSignaller->editProofOrdering(proof);
}

void Model::deleteProof(int id)
{
    modelSignaller->deleteProof(id);
}