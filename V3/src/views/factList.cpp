#include <iostream>

#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

#include "model.h"
#include "database/methods.h"
#include "widgets/resizableStackedWidget.h"
#include "views/expandingFactWidget.h"
#include "views/factListView.h"

#include "views/factList.h"

FactList::FactList(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactListView *factListView, QWidget *parent)
    : QWidget(parent)
{
    this->fact = fact;
    this->model = model;
    this->pageStack = pageStack;
    this->factListView = factListView;



    layout = new QVBoxLayout(this);
    layout->setContentsMargins(11, 0, 0, 11);

    // If this is not the root fact, then add a label
    // showing the name of the section
    if (fact.parent != -1) {
        sectionNameLabel = new QLabel(QString::fromStdString(fact.name));
        layout->addWidget(sectionNameLabel);
    }
    else {
        sectionNameLabel = nullptr;
    }

    // Populate the list of children but don't add to the layout
    isCurrentlyBuilt = false;

    idChildSectionMap = std::map<int, FactList*>();
    idChildFactMap = std::map<int, ExpandingFactWidget*>();
    idChildMap = std::map<int, std::pair<Fact, QWidget*> >();

    std::vector<Fact> facts = findChildFacts(fact.id);

    for (size_t i = 0; i < facts.size(); ++i) {
        if (facts[i].type == "Section") {
            FactList *factList = new FactList(facts[i], model, pageStack, factListView);
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



    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factOrderingEdited(Fact)), this, SLOT(factOrderingEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));
}

FactList::~FactList()
{
    factListView->idFactListMap.erase(fact.id);
}

void FactList::paintEvent(QPaintEvent *)
{
    if (fact.parent != -1) {
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

void FactList::buildLayout()
{  
    if (!isCurrentlyBuilt) {
        isCurrentlyBuilt = true;

        for (auto it = idChildSectionMap.begin(); it != idChildSectionMap.end(); it++) {
            it->second->buildLayout();
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

void FactList::factAddedSlot(Fact fact)
{
    if (fact.parent == this->fact.id) {
        if (fact.type == "Section") {
            FactList *factWidget = new FactList(fact, model, pageStack, factListView);
            idChildSectionMap.insert(std::pair<int, FactList*>(fact.id, factWidget));
            factListView->idFactListMap.insert(std::pair<int, FactList*>(fact.id, factWidget));

            if (isCurrentlyBuilt) {
                insertFactWidget(fact, factWidget);
                factWidget->buildLayout();
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
                        factWidget->buildLayout();
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