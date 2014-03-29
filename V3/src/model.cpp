#include <iostream>

#include "model.h"

Model::Model()
{
    courseSelected = factSelected = proofSelected = false;
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
    this->course = course;
    emit courseSelectedChanged(course);
}

void Model::addCourse(Course course)
{
    emit courseAdded(course);
}

void Model::editCourse(Course course)
{
    emit courseEdited(course);
}

void Model::deleteCourse(int id)
{
    emit courseDeleted(id);
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
    this->fact = fact;
    emit factSelectedChanged(fact);
}

void Model::addFact(Fact fact)
{
    emit factAdded(fact);
}

void Model::editFact(Fact fact)
{
    emit factEdited(fact);
}

void Model::deleteFact(int id)
{
    emit factDeleted(id);
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
    this->proof = proof;
    emit proofSelectedChanged(proof);
}

void Model::addProof(Proof proof)
{
    emit proofAdded(proof);
}

void Model::editProof(Proof proof)
{
    emit proofEdited(proof);
}

void Model::deleteProof(int id)
{
    emit proofDeleted(id);
}