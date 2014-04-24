#include <iostream>

#include "database/methods.h"
#include "latex/latexRenderer.h"
#include "latex/renderQueue.h"

#include "model.h"

//   #####  ######  #####  ##    ##    ##    ##      ##      ###### ######
//  ##   ##   ##   ##   ## ###   ##   ####   ##      ##      ##     ##   ##
//   ##       ##   ##      ####  ##  ##  ##  ##      ##      ##     ##   ##
//    ###     ##   ##      ## ## ## ##    ## ##      ##      ####   ######
//      ##    ##   ##  ### ##  #### ######## ##      ##      ##     ##  ##
//  ##   ##   ##   ##   ## ##   ### ##    ## ##      ##      ##     ##   ##
//   #####  ######  #####  ##    ## ##    ## ####### ####### ###### ##   ##

ModelSignaller::ModelSignaller(QObject *parent)
    : QObject(parent)
{
    renderer = new LatexRenderer();
    renderer->moveToThread(&renderThread);

    renderQueue = new RenderQueue();
    renderQueue->moveToThread(&renderThread);

    renderThread.start();

    connect(this, SIGNAL(requestRenderFact(Fact)), renderQueue, SLOT(queueFact(Fact)), Qt::QueuedConnection);
    connect(this, SIGNAL(requestRenderProof(Proof)), renderQueue, SLOT(queueProof(Proof)), Qt::QueuedConnection);

    connect(renderQueue, SIGNAL(supplyFact(Fact)), renderer, SLOT(renderFact(Fact)), Qt::QueuedConnection);
    connect(renderQueue, SIGNAL(supplyProof(Proof)), renderer, SLOT(renderProof(Proof)), Qt::QueuedConnection);

    connect(renderer, SIGNAL(factRendered(Fact, bool)), renderQueue, SLOT(requestText()), Qt::QueuedConnection);
    connect(renderer, SIGNAL(proofRendered(Proof, bool)), renderQueue, SLOT(requestText()), Qt::QueuedConnection);

    connect(renderer, SIGNAL(factRendered(Fact, bool)), this, SIGNAL(factRendered(Fact, bool)), Qt::QueuedConnection);
    connect(renderer, SIGNAL(proofRendered(Proof, bool)), this, SIGNAL(proofRendered(Proof, bool)), Qt::QueuedConnection);
}

ModelSignaller::~ModelSignaller()
{
    renderThread.quit();
    renderThread.wait(1000);

    delete renderQueue;
    delete renderer;
}

Course ModelSignaller::addCourse(std::string name)
{
    Course course = Database::findCourse(Database::addCourse(name));

    emit courseAdded(course);

    return course;
}

void ModelSignaller::editCourse(Course course)
{
    Database::editCourse(course);
    emit courseEdited(course);
}

void ModelSignaller::editCourseOrdering(Course course)
{
    Database::editCourseOrdering(course);
    emit courseOrderingEdited(course);
}

void ModelSignaller::deleteCourse(int id)
{
    Database::deleteCourse(id);
    emit courseDeleted(id);
}

Fact ModelSignaller::addFact(int parent, std::string name, std::string type)
{
    Fact fact = Database::findFact(Database::addFact(parent, name, type));

    emit factAdded(fact);

    return fact;
}

void ModelSignaller::editFact(Fact fact)
{
    Database::editFact(fact);
    emit factEdited(fact);
}

void ModelSignaller::editFactOrdering(Fact fact)
{
    Database::editFactOrdering(fact);
    emit factOrderingEdited(fact);
}

void ModelSignaller::renderFact(Fact fact)
{
    emit requestRenderFact(fact);
}

void ModelSignaller::deleteFact(int id)
{
    Database::deleteFact(id);
    emit factDeleted(id);
}

Proof ModelSignaller::addProof(int fact, std::string name)
{
    Proof proof = Database::findProof(Database::addProof(fact, name));

    emit proofAdded(proof);

    return proof;
}

void ModelSignaller::editProof(Proof proof)
{
    Database::editProof(proof);
    emit proofEdited(proof);
}

void ModelSignaller::editProofOrdering(Proof proof)
{
    Database::editProofOrdering(proof);
    emit proofOrderingEdited(proof);
}

void ModelSignaller::renderProof(Proof proof)
{
    emit requestRenderProof(proof);
}

void ModelSignaller::deleteProof(int id)
{
    Database::deleteProof(id);
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
    connect(modelSignaller, SIGNAL(factRendered(Fact, bool)), this, SIGNAL(factRendered(Fact, bool)));
    connect(modelSignaller, SIGNAL(factDeleted(int)), this, SIGNAL(factDeleted(int)));

    connect(modelSignaller, SIGNAL(proofAdded(Proof)), this, SIGNAL(proofAdded(Proof)));
    connect(modelSignaller, SIGNAL(proofEdited(Proof)), this, SIGNAL(proofEdited(Proof)));
    connect(modelSignaller, SIGNAL(proofOrderingEdited(Proof)), this, SIGNAL(proofOrderingEdited(Proof)));
    connect(modelSignaller, SIGNAL(proofRendered(Proof, bool)), this, SIGNAL(proofRendered(Proof, bool)));
    connect(modelSignaller, SIGNAL(proofDeleted(int)), this, SIGNAL(proofDeleted(int)));

    connect(modelSignaller, SIGNAL(courseEdited(Course)), this, SLOT(courseEditedSlot(Course)));
    connect(modelSignaller, SIGNAL(courseOrderingEdited(Course)), this, SLOT(courseOrderingEditedSlot(Course)));
    connect(modelSignaller, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(modelSignaller, SIGNAL(factOrderingEdited(Fact)), this, SLOT(factOrderingEditedSlot(Fact)));
    connect(modelSignaller, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
    connect(modelSignaller, SIGNAL(proofOrderingEdited(Proof)), this, SLOT(proofOrderingEditedSlot(Proof)));
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

Course Model::addCourse(std::string name)
{
    return modelSignaller->addCourse(name);
}

void Model::editCourse(Course course)
{
    modelSignaller->editCourse(course);
}

void Model::editCourseOrdering(Course course)
{
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

Fact Model::addFact(int parent, std::string name, std::string type)
{
    return modelSignaller->addFact(parent, name, type);
}

void Model::editFact(Fact fact)
{
    modelSignaller->editFact(fact);
}

void Model::editFactOrdering(Fact fact)
{
    modelSignaller->editFactOrdering(fact);
}

void Model::renderFact(Fact fact)
{
    modelSignaller->renderFact(fact);
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

Proof Model::addProof(int fact, std::string name)
{
    return modelSignaller->addProof(fact, name);
}

void Model::editProof(Proof proof)
{
    modelSignaller->editProof(proof);
}

void Model::editProofOrdering(Proof proof)
{
    modelSignaller->editProofOrdering(proof);
}

void Model::renderProof(Proof proof)
{
    modelSignaller->renderProof(proof);
}

void Model::deleteProof(int id)
{
    modelSignaller->deleteProof(id);
}

void Model::courseEditedSlot(Course course)
{
    if (course.id == this->course.id) {
        this->course = course;
    }
}

void Model::courseOrderingEditedSlot(Course course)
{
    if (course.id == this->course.id) {
        this->course = course;
    }
}

void Model::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
    }
}

void Model::factOrderingEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
    }
}

void Model::proofEditedSlot(Proof proof)
{
    if (proof.id == this->proof.id) {
        this->proof = proof;
    }
}

void Model::proofOrderingEditedSlot(Proof proof)
{
    if (proof.id == this->proof.id) {
        this->proof = proof;
    }
}