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

    sectionNameLabel = new QLabel(QString::fromStdString(fact.name));

    if (fact.parent != -1) {
        layout->addWidget(sectionNameLabel);
    }

    std::vector<Fact> facts = findChildFacts(fact.id);
    idChildMap = std::map<int, std::pair<Fact, QWidget*> >();

    for (size_t i = 0; i < facts.size(); ++i) {
        factAddedSlot(facts[i]);
    }



    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));



    idFactListMap->insert(std::pair<int, FactList*>(fact.id, this));
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

void FactList::factAddedSlot(Fact fact)
{
    if (fact.parent == this->fact.id) {
        int position = idChildMap.size() + 1;

        for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
            if (it->second.first.ordering > fact.ordering) {
                position = std::min(position, layout->indexOf(it->second.second));
            }
        }

        if (fact.type == "Section") {
            FactList *factList = new FactList(fact, model, pageStack, idFactListMap);
            layout->insertWidget(position, factList);
            idChildMap.insert(std::pair<int, std::pair<Fact, QWidget*> >(fact.id, std::pair<Fact, QWidget*>(fact, factList)));
        }
        else {
            ExpandingFactWidget *factWidget = new ExpandingFactWidget(fact, model, pageStack);
            layout->insertWidget(position, factWidget);
            idChildMap.insert(std::pair<int, std::pair<Fact, QWidget*> >(fact.id, std::pair<Fact, QWidget*>(fact, factWidget)));
        }
    }
}

void FactList::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        sectionNameLabel->setText(QString::fromStdString(fact.name));
    }
    else if (fact.type != "Section" && fact.parent == this->fact.id) {
        auto item = idChildMap.at(fact.id);
        int i = layout->indexOf(item.second);

        delete layout->takeAt(i)->widget();
        idChildMap.erase(fact.id);

        ExpandingFactWidget *factWidget = new ExpandingFactWidget(fact, model, pageStack);
        layout->insertWidget(i, factWidget);
        idChildMap.insert(std::pair<int, std::pair<Fact, QWidget*> >(fact.id, std::pair<Fact, QWidget*>(fact, factWidget)));
    }
}

void FactList::factDeletedSlot(int id)
{
    if (idChildMap.count(id) != 0) {
        auto item = idChildMap.at(id);
        layout->removeWidget(item.second);
        delete item.second;
        idChildMap.erase(id);
    }
}