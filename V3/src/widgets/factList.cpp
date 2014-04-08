#include <iostream>

#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

#include "model.h"
#include "database/methods.h"
#include "widgets/expandingFactWidget.h"
#include "widgets/resizableStackedWidget.h"

#include "widgets/factList.h"

FactList::FactList(Fact fact, Model *model, ResizableStackedWidget *pageStack, std::map<int, FactList*> *idFactListMap, QWidget *parent)
    : QWidget(parent)
{
    this->fact = fact;
    this->model = model;
    this->pageStack = pageStack;
    this->idFactListMap = idFactListMap;



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

    idChildSectionMap = std::map<int, std::pair<Fact, FactList*> >();
    idChildMap = std::map<int, std::pair<Fact, QWidget*> >();

    std::vector<Fact> facts = findChildFacts(fact.id);

    for (size_t i = 0; i < facts.size(); ++i) {
        if (facts[i].type == "Section") {
            FactList *factList = new FactList(facts[i], model, pageStack, idFactListMap);
            idChildSectionMap.insert(std::pair<int, std::pair<Fact, FactList*> >(facts[i].id, std::pair<Fact, FactList*>(facts[i], factList)));
            idFactListMap->insert(std::pair<int, FactList*>(facts[i].id, factList));
        }
        else {
            ExpandingFactWidget *factWidget = new ExpandingFactWidget(facts[i], model, pageStack);
            insertFactWidget(facts[i], factWidget);
        }
    }



    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));
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
    isCurrentlyBuilt = true;

    for (auto it = idChildSectionMap.begin(); it != idChildSectionMap.end(); it++) {
        it->second.second->buildLayout();
        insertFactWidget(it->second.first, it->second.second);
    }

    for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
        it->second.second->show();
    }

    if (sectionNameLabel != nullptr) {
        sectionNameLabel->show();
    }

    show();
}

void FactList::destroyLayout()
{
    isCurrentlyBuilt = false;

    hide();

    if (sectionNameLabel != nullptr) {
        sectionNameLabel->hide();
    }

    for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
        it->second.second->hide();
    }

    for (auto it = idChildSectionMap.begin(); it != idChildSectionMap.end(); it++) {
        layout->removeWidget(it->second.second);
        idChildMap.erase(it->second.first.id);
        it->second.second->destroyLayout();
    }
}

void FactList::factAddedSlot(Fact fact)
{
    if (fact.parent == this->fact.id) {
        if (fact.type == "Section") {
            FactList *factWidget = new FactList(fact, model, pageStack, idFactListMap);
            idChildSectionMap.insert(std::pair<int, std::pair<Fact, FactList*> >(fact.id, std::pair<Fact, FactList*>(fact, factWidget)));
            idFactListMap->insert(std::pair<int, FactList*>(fact.id, factWidget));

            if (isCurrentlyBuilt) {
                insertFactWidget(fact, factWidget);
            }
        }
        else {
            ExpandingFactWidget *factWidget = new ExpandingFactWidget(fact, model, pageStack);
            insertFactWidget(fact, factWidget);
        }
    }
}

void FactList::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        // Possibly just change the name shown
        sectionNameLabel->setText(QString::fromStdString(fact.name));
    }
    else if (fact.parent == this->fact.id) {
        // Or possibly have to move widgets around because
        // the order might have changed

        if (idChildSectionMap.count(fact.id) > 0) {
            auto item = idChildSectionMap.at(fact.id);

            idChildSectionMap.erase(fact.id);
            idChildSectionMap.insert(std::pair<int, std::pair<Fact, FactList*> >(fact.id, std::pair<Fact, FactList*>(fact, item.second)));
        }

        if (idChildMap.count(fact.id)) {
            auto item = idChildMap.at(fact.id);

            item.second->hide();
            layout->removeWidget(item.second);
            idChildMap.erase(fact.id);

            insertFactWidget(fact, item.second);
            idChildMap.insert(std::pair<int, std::pair<Fact, QWidget*> >(fact.id, std::pair<Fact, QWidget*>(fact, item.second)));
        }
    }
}

void FactList::factDeletedSlot(int id)
{
    if (idChildSectionMap.count(id) > 0) {
        if (idChildMap.count(id) == 0) {
            delete idChildSectionMap.at(id).second;
        }

        idChildSectionMap.erase(id);
        idFactListMap->erase(id);
    }

    if (idChildMap.count(id) > 0) {
        auto item = idChildMap.at(id);

        layout->removeWidget(item.second);
        delete item.second;

        idChildMap.erase(id);
    }
}