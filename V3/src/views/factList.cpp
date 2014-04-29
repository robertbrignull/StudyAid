#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

#include "model.h"
#include "database/methods.h"
#include "forms/factForm.h"
#include "forms/sectionForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/dialog.h"
#include "views/expandingFactWidget.h"
#include "views/factListView.h"

#include "views/factList.h"

FactList::FactList(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactListView *factListView, FactForm *factAddForm, Dialog *factAddDialog, SectionForm *sectionEditForm, Dialog *sectionEditDialog, QWidget *parent)
    : QWidget(parent)
{
    this->fact = fact;
    this->model = model;
    this->pageStack = pageStack;
    this->factListView = factListView;
    this->factAddForm = factAddForm;
    this->factAddDialog = factAddDialog;
    this->sectionEditForm = sectionEditForm;
    this->sectionEditDialog = sectionEditDialog;



    layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 0, 0, 11);



    // If this is not the root fact, then add a label
    // showing the name of the section
    if (fact.parent != -1) {
        sectionNameLabel = new QLabel(QString::fromStdString(fact.name));
        sectionNameLabel->setWordWrap(true);
        sectionNameLabel->setScaledContents(true);

        moveButton = new ImageButton(QPixmap(":/images/move_black.png"), QSize(24, 24));
        moveAboveButton = new ImageButton(QPixmap(":/images/arrow_up_black.png"), QSize(24, 24));
        moveBelowButton = new ImageButton(QPixmap(":/images/arrow_down_black.png"), QSize(24, 24));

        deleteSectionButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(24, 24));

        sectionDeleteDialog = new Dialog(this, nullptr, "Are you sure you want to delete this section?", "Delete", "Cancel");

        editSectionButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(24, 24));

        addFactButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(24, 24));

        QHBoxLayout *headLayout = new QHBoxLayout();

        headLayout->addWidget(sectionNameLabel);
        headLayout->addWidget(deleteSectionButton);
        headLayout->addWidget(editSectionButton);
        headLayout->addWidget(moveBelowButton);
        headLayout->addWidget(moveAboveButton);
        headLayout->addWidget(moveButton);
        headLayout->addWidget(addFactButton);

        layout->addLayout(headLayout);

        deactivateMoveMode();
    }
    else {
        sectionNameLabel = nullptr;
        moveButton = moveAboveButton = moveBelowButton = deleteSectionButton = editSectionButton = addFactButton = nullptr;
        sectionDeleteDialog = nullptr;

        sectionNameLabel = new QLabel(QString::fromStdString(Database::findCourseByRootFact(fact.id).name));
        sectionNameLabel->setWordWrap(true);
        sectionNameLabel->setScaledContents(true);

        addFactButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(24, 24));

        QHBoxLayout *headLayout = new QHBoxLayout();
        headLayout->addWidget(sectionNameLabel);
        headLayout->addWidget(addFactButton);
        layout->addLayout(headLayout);
    }

    // Populate the list of children but don't add to the layout
    isCurrentlyBuilt = false;

    idChildSectionMap = std::map<int, FactList*>();
    idChildFactMap = std::map<int, ExpandingFactWidget*>();
    idChildMap = std::map<int, std::pair<Fact, QWidget*> >();

    std::vector<Fact> facts = Database::findChildFacts(fact.id);

    for (size_t i = 0; i < facts.size(); ++i) {
        if (facts[i].type == "Section") {
            FactList *factList = new FactList(facts[i], model, pageStack, factListView, factAddForm, factAddDialog, sectionEditForm, sectionEditDialog);
            idChildSectionMap.insert(std::pair<int, FactList*>(facts[i].id, factList));
        }
        else {
            ExpandingFactWidget *factWidget = new ExpandingFactWidget(facts[i], model, pageStack, factListView);
            idChildFactMap.insert(std::pair<int, ExpandingFactWidget*>(facts[i].id, factWidget));
            insertFactWidget(facts[i], factWidget);
        }
    }

    // Add this widget into the master map
    factListView->idFactListMap.insert(std::pair<int, FactList*>(fact.id, this));



    if (fact.parent != -1) {
        connect(moveButton, SIGNAL(clicked()), this, SLOT(moveButtonClickedSlot()));
        connect(moveAboveButton, SIGNAL(clicked()), this, SLOT(moveAboveButtonClickedSlot()));
        connect(moveBelowButton, SIGNAL(clicked()), this, SLOT(moveBelowButtonClickedSlot()));

        connect(this, SIGNAL(moveButtonClicked(Fact)), factListView, SIGNAL(moveButtonClicked(Fact)));
        connect(this, SIGNAL(moveCompleted()), factListView, SIGNAL(moveCompleted()));

        connect(deleteSectionButton, SIGNAL(clicked()), sectionDeleteDialog, SLOT(show()));

        connect(sectionDeleteDialog, SIGNAL(accepted()), this, SLOT(sectionDeleteDialogAccepted()));
        connect(sectionDeleteDialog, SIGNAL(rejected()), sectionDeleteDialog, SLOT(close()));

        connect(editSectionButton, SIGNAL(clicked()), this, SLOT(sectionEditButtonClicked()));
    }

    connect(factListView, SIGNAL(moveButtonClicked(Fact)), this, SLOT(activateMoveMode(Fact)));
    connect(factListView, SIGNAL(moveCompleted()), this, SLOT(deactivateMoveMode()));

    connect(addFactButton, SIGNAL(clicked()), this, SLOT(factAddButtonClicked()));

    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factOrderingEdited(Fact)), this, SLOT(factOrderingEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));

    if (fact.parent == -1) {
        connect(model, SIGNAL(courseEdited(Course)), this, SLOT(courseEditedSlot(Course)));
    }
}

FactList::~FactList()
{
    factListView->idFactListMap.erase(fact.id);
}

void FactList::paintEvent(QPaintEvent *)
{
    if (fact.parent != -1 && !isRootSection) {
        QPainter painter(this);

        painter.setPen(QPen(QBrush(QColor(QColor(66, 139, 202))), 2));

        painter.drawLine(1, 1, 31, 1);
        painter.drawLine(1, 1, 1, size().height()-1);
        painter.drawLine(1, size().height()-1, 31, size().height()-1);
    }
}

void FactList::insertFactWidget(Fact fact, QWidget *factWidget)
{
    int position = idChildMap.size() + 1;

    for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
        if (it->second.first.ordering > fact.ordering) {
            position = std::min(position, layout->indexOf(it->second.second));
        }
    }

    layout->insertWidget(position, factWidget);
    factWidget->show();
    idChildMap.insert(std::pair<int, std::pair<Fact, QWidget*> >(fact.id, std::pair<Fact, QWidget*>(fact, factWidget)));
}

void FactList::buildLayout(bool isRootSection)
{  
    if (!isCurrentlyBuilt) {
        isCurrentlyBuilt = true;
        this->isRootSection = isRootSection;

        for (auto it = idChildSectionMap.begin(); it != idChildSectionMap.end(); it++) {
            it->second->buildLayout(false);
            insertFactWidget(it->second->fact, it->second);
        }

        for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
            it->second.second->show();
        }

        if (sectionNameLabel != nullptr) {
            sectionNameLabel->show();
        }

        show();
    }
}

void FactList::destroyLayout()
{
    if (isCurrentlyBuilt) {
        isCurrentlyBuilt = false;
        isRootSection = false;

        hide();

        if (sectionNameLabel != nullptr) {
            sectionNameLabel->hide();
        }

        for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
            it->second.second->hide();
        }

        for (auto it = idChildSectionMap.begin(); it != idChildSectionMap.end(); it++) {
            layout->removeWidget(it->second);
            it->second->setParent(0);

            idChildMap.erase(it->second->fact.id);
            it->second->destroyLayout();
        }
    }
}

void FactList::moveButtonClickedSlot()
{
    if (inMoveMode) {
        emit moveCompleted();
    }
    else {
        emit moveButtonClicked(fact);
    }
}

void FactList::moveAboveButtonClickedSlot()
{
    moveFact.parent = fact.parent;
    moveFact.ordering = fact.ordering;

    model->editFactOrdering(moveFact);

    emit moveCompleted();
}

void FactList::moveBelowButtonClickedSlot()
{
    moveFact.parent = fact.parent;
    moveFact.ordering = fact.ordering + 1;

    model->editFactOrdering(moveFact);

    emit moveCompleted();
}

void FactList::activateMoveMode(Fact fact)
{
    // Very important we don't enter move mode if it's one of our ancestors
    // being moved. Making a section its own parent causes problems!
    bool isAncestor = false;
    Fact currentFact = this->fact;

    while (currentFact.parent != -1) {
        FactList *factList = factListView->idFactListMap.at(currentFact.parent);
        if (factList->fact.id == fact.id) {
            isAncestor = true;
            break;
        }
        currentFact = factList->fact;
    }



    inMoveMode = true;

    addFactButton->hide();

    if (this->fact.parent != -1) {
        deleteSectionButton->hide();
        editSectionButton->hide();

        if (fact.id == this->fact.id) {
            moveButton->show();
            moveAboveButton->hide();
            moveBelowButton->hide();
        }
        else {
            moveButton->hide();

            if (!isAncestor) {
                moveFact = fact;

                moveAboveButton->show();
                moveBelowButton->show();
            }
            else {
                moveAboveButton->hide();
                moveBelowButton->hide();
            }
        }
    }
}

void FactList::deactivateMoveMode()
{
    inMoveMode = false;

    addFactButton->show();

    if (this->fact.parent != -1) {
        deleteSectionButton->show();
        editSectionButton->show();

        moveButton->show();
        moveAboveButton->hide();
        moveBelowButton->hide();
    }
}

void FactList::factAddButtonClicked()
{
    Fact newFact = Fact();
    newFact.parent = fact.id;

    factAddForm->setData(newFact);

    factAddDialog->show();
}

void FactList::sectionEditButtonClicked()
{
    sectionEditDialog->show();
    sectionEditForm->setData(fact);
}

void FactList::sectionDeleteDialogAccepted()
{
    sectionDeleteDialog->close();

    model->deleteFact(fact.id);
}

void FactList::courseEditedSlot(Course course)
{
    if (course.root_fact == fact.id) {
        sectionNameLabel->setText(QString::fromStdString(course.name));
    }
}

void FactList::factAddedSlot(Fact fact)
{
    if (fact.parent == this->fact.id) {
        if (fact.type == "Section") {
            FactList *factWidget = new FactList(fact, model, pageStack, factListView, factAddForm, factAddDialog, sectionEditForm, sectionEditDialog);
            idChildSectionMap.insert(std::pair<int, FactList*>(fact.id, factWidget));
            factListView->idFactListMap.insert(std::pair<int, FactList*>(fact.id, factWidget));

            if (isCurrentlyBuilt) {
                insertFactWidget(fact, factWidget);
                factWidget->buildLayout(false);
            }
        }
        else {
            ExpandingFactWidget *factWidget = new ExpandingFactWidget(fact, model, pageStack, factListView);
            idChildFactMap.insert(std::pair<int, ExpandingFactWidget*>(fact.id, factWidget));
            insertFactWidget(fact, factWidget);
        }
    }
}

void FactList::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        sectionNameLabel->setText(QString::fromStdString(fact.name));
    }
}

void FactList::factOrderingEditedSlot(Fact fact)
{
    if (fact.parent == this->fact.id) {
        // Update orderings on children
        for (auto it = idChildSectionMap.begin(); it != idChildSectionMap.end(); it++) {
            if (it->second->fact.ordering >= fact.ordering) {
                it->second->fact.ordering += 1;
            }
        }

        for (auto it = idChildFactMap.begin(); it != idChildFactMap.end(); it++) {
            if (it->second->fact.ordering >= fact.ordering) {
                it->second->fact.ordering += 1;
            }
        }

        for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
            if (it->second.first.ordering >= fact.ordering) {
                it->second.first.ordering += 1;
            }
        }

        // Locate where the fact came from
        FactList *oldParentFactList = nullptr;

        for (auto it = factListView->idFactListMap.begin(); it != factListView->idFactListMap.end(); it++) {
            if (it->second->idChildFactMap.count(fact.id) > 0 || it->second->idChildSectionMap.count(fact.id) > 0) {
                oldParentFactList = it->second;
                break;
            }
        }

        // Remove the fact widget from where it was
        if (oldParentFactList != nullptr) {
            QWidget *movingFactWidget = nullptr;
            
            if (oldParentFactList->idChildMap.count(fact.id) > 0) {
                movingFactWidget = oldParentFactList->idChildMap.at(fact.id).second;
                oldParentFactList->idChildMap.erase(fact.id);

                movingFactWidget->hide();
                layout->removeWidget(movingFactWidget);
                movingFactWidget->setParent(0);
            }

            if (oldParentFactList->idChildFactMap.count(fact.id) > 0) {
                movingFactWidget = oldParentFactList->idChildFactMap.at(fact.id);
                oldParentFactList->idChildFactMap.erase(fact.id);
            }

            if (oldParentFactList->idChildSectionMap.count(fact.id) > 0) {
                movingFactWidget = oldParentFactList->idChildSectionMap.at(fact.id);
                oldParentFactList->idChildSectionMap.erase(fact.id);
            }

            // And add it into this FactList, updating the ordering
            if (movingFactWidget != nullptr) {
                if (fact.type == "Section") {
                    FactList *factWidget = (FactList*) movingFactWidget;

                    factWidget->fact = fact;
                    idChildSectionMap.insert(std::pair<int, FactList*>(fact.id, factWidget));

                    if (isCurrentlyBuilt) {
                        insertFactWidget(fact, factWidget);
                        factWidget->buildLayout(false);
                    }
                }
                else {
                    ExpandingFactWidget *factWidget = (ExpandingFactWidget*) movingFactWidget;

                    factWidget->fact = fact;
                    idChildFactMap.insert(std::pair<int, ExpandingFactWidget*>(fact.id, factWidget));

                    insertFactWidget(fact, factWidget);
                }
            }
        }
    }
}

void FactList::factDeletedSlot(int id)
{
    if (idChildMap.count(id) > 0) {
        auto item = idChildMap.at(id);

        item.second->hide();
        layout->removeWidget(item.second);
        item.second->setParent(0);

        idChildMap.erase(id);
    }

    if (idChildSectionMap.count(id) > 0) {
        delete idChildSectionMap.at(id);
        idChildSectionMap.erase(id);
    }

    if (idChildFactMap.count(id) > 0) {
        delete idChildFactMap.at(id);
        idChildFactMap.erase(id);
    }
}