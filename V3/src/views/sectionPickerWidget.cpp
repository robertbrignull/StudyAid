#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>

#include "model.h"
#include "database/methods.h"
#include "widgets/clickableQLabel.h"

#include "views/sectionPickerWidget.h"

SectionPickerWidget::SectionPickerWidget(Fact fact, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->fact = fact;
    this->model = model;



    layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 0, 0, 5);



    sectionLabel = new ClickableQLabel((fact.parent != -1) ? QString::fromStdString(fact.name) : "All");

    sectionLabel->setWordWrap(true);
    sectionLabel->setScaledContents(true);

    layout->addWidget(sectionLabel);



    std::vector<Fact> facts = Database::findChildSections(fact.id);
    idSectionPickerMap = std::map<int, SectionPickerWidget*>();

    for (size_t i = 0; i < facts.size(); ++i) {
        factAddedSlot(facts[i]);
    }



    connect(sectionLabel, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(fact.id);
    });

    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factOrderingEdited(Fact)), this, SLOT(factOrderingEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));
}

void SectionPickerWidget::paintEvent(QPaintEvent *)
{
    if (fact.parent != -1) {
        QPainter painter(this);

        painter.setPen(QPen(QBrush(QColor(QColor(66, 139, 202))), 2));

        painter.drawLine(1, 1, 13, 1);
        painter.drawLine(1, 1, 1, size().height()-1);
        painter.drawLine(1, size().height()-1, 13, size().height()-1);
    }
}

void SectionPickerWidget::sectionSelectedSlot(int id)
{
    emit sectionSelected(id);
}

void SectionPickerWidget::factAddedSlot(Fact fact)
{
    if (fact.type == "Section" && fact.parent == this->fact.id) {
        insertSectionPickerWidget(new SectionPickerWidget(fact, model));
    }
}

void SectionPickerWidget::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
        sectionLabel->setText(QString::fromStdString(fact.name));
    }
}

void SectionPickerWidget::factOrderingEditedSlot(Fact fact)
{
    factDeletedSlot(fact.id);

    if (fact.type == "Section" && fact.parent == this->fact.id) {
        // Update the orderings of other section child section pickers
        for (auto it = idSectionPickerMap.begin(); it != idSectionPickerMap.end(); it++) {
            if (it->second->fact.ordering >= fact.ordering) {
                it->second->fact.ordering += 1;
            }
        }

        insertSectionPickerWidget(new SectionPickerWidget(fact, model));
    }
}

void SectionPickerWidget::factDeletedSlot(int id)
{
    if (idSectionPickerMap.count(id) != 0) {
        auto item = idSectionPickerMap.at(id);
        layout->removeWidget(item);
        delete item;
        idSectionPickerMap.erase(id);
    }
}

void SectionPickerWidget::insertSectionPickerWidget(SectionPickerWidget *sectionPickerWidget)
{
    int position = idSectionPickerMap.size() + 1;

    for (auto it = idSectionPickerMap.begin(); it != idSectionPickerMap.end(); it++) {
        if (it->second->fact.ordering > sectionPickerWidget->fact.ordering) {
            position = std::min(position, layout->indexOf(it->second));
        }
    }

    layout->insertWidget(position, sectionPickerWidget);

    idSectionPickerMap.insert(std::pair<int, SectionPickerWidget*>(sectionPickerWidget->fact.id, sectionPickerWidget));

    connect(sectionPickerWidget, SIGNAL(sectionSelected(int)), this, SLOT(sectionSelectedSlot(int)));
}