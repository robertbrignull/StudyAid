#include <QHBoxLayout>

#include "model.h"
#include "database/methods.h"
#include "forms/factForm.h"
#include "forms/sectionForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/dialog.h"
#include "views/factList.h"

#include "views/factListView.h"

FactListView::FactListView(Course course, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->course = course;
    this->model = model;
    this->pageStack = pageStack;



    factAddForm = new FactForm();
    factAddDialog = new Dialog(this, factAddForm, "Add a new fact...", "Add", "Cancel");

    sectionEditForm = new SectionForm();
    sectionEditDialog = new Dialog(this, sectionEditForm, "Edit the section...", "Edit", "Cancel");



    idFactListMap = std::map<int, FactList*>();

    currentFactList = new FactList(Database::findFact(course.root_fact), model, pageStack, this, factAddForm, factAddDialog, sectionEditForm, sectionEditDialog);
    idFactListMap.insert(std::pair<int, FactList*>(course.root_fact, currentFactList));

    currentFactList->buildLayout(true);

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(currentFactList);



    connect(factAddDialog, SIGNAL(accepted()), this, SLOT(factAddFormCompleted()));
    connect(factAddDialog, SIGNAL(rejected()), factAddDialog, SLOT(close()));

    connect(sectionEditDialog, SIGNAL(accepted()), this, SLOT(sectionEditFormCompleted()));
    connect(sectionEditDialog, SIGNAL(rejected()), sectionEditDialog, SLOT(close()));
}

FactListView::~FactListView()
{
    currentFactList->destroyLayout();

    while (layout->count() > 0) {
        layout->takeAt(0);
    }

    while (idFactListMap.size() > 0) {
        delete idFactListMap.begin()->second;
    }
}

void FactListView::selectSection(int id)
{
    currentFactList->destroyLayout();
    
    while (layout->count() > 0) {
        layout->takeAt(0);
    }

    currentFactList = idFactListMap.at(id);
    currentFactList->buildLayout(true);

    layout->addWidget(currentFactList);
    currentFactList->show();
}

void FactListView::factAddFormCompleted()
{
    Fact data = factAddForm->getData();

    Fact newFact = model->addFact(data.parent, data.name, data.type);

    factAddDialog->close();

    if (newFact.type != "Section") {
        model->setFactSelected(newFact);
        pageStack->setCurrentIndex(2);
    }
}

void FactListView::sectionEditFormCompleted()
{
    Fact section = sectionEditForm->getData();

    model->editFact(section);

    sectionEditDialog->close();
}