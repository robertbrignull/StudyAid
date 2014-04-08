#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "model.h"
#include "database/methods.h"
#include "widgets/clickableQLabel.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/dialog.h"
#include "forms/factForm.h"

#include "views/sectionPickerWidget.h"

SectionPickerWidget::SectionPickerWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->fact = fact;
    this->model = model;
    this->pageStack = pageStack;


    factAddForm = new FactForm();
    factAddDialog = new Dialog(this, factAddForm, "Add a new fact...", "Add", "Cancel");

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);



    QHBoxLayout *sectionLayout = new QHBoxLayout();
    sectionLabel = new ClickableQLabel((fact.parent != -1) ? fact.name : "All");
    addFactButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(16, 16));

    sectionLayout->addWidget(sectionLabel);
    sectionLayout->addStretch(1);
    sectionLayout->addWidget(addFactButton);

    layout->addLayout(sectionLayout);



    std::vector<Fact> facts = findChildSections(fact.id);
    idSectionPickerMap = std::map<int, std::pair<Fact, SectionPickerWidget*> >();

    for (size_t i = 0; i < facts.size(); ++i) {
        factAddedSlot(facts[i]);
    }



    connect(sectionLabel, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(fact.id);
    });

    connect(addFactButton, SIGNAL(clicked()), factAddDialog, SLOT(show()));

    connect(factAddDialog, SIGNAL(cancelled()), factAddDialog, SLOT(close()));
    connect(factAddDialog, SIGNAL(completed()), this, SLOT(factAddFormCompleted()));

    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));
}

void SectionPickerWidget::sectionSelectedSlot(int id)
{
    emit sectionSelected(id);
}

void SectionPickerWidget::factAddFormCompleted()
{
    Fact data = factAddForm->getData();

    Fact newFact = findFact(addFact(fact.id, data.name, data.type));

    model->addFact(newFact);

    factAddDialog->close();

    if (newFact.type != "Section") {
        model->setFactSelected(newFact);
        pageStack->setCurrentIndex(2);
    }
}

void SectionPickerWidget::factAddedSlot(Fact fact)
{
    if (fact.type == "Section" && fact.parent == this->fact.id) {
        int position = idSectionPickerMap.size();

        for (auto it = idSectionPickerMap.begin(); it != idSectionPickerMap.end(); it++) {
            if (it->second.first.ordering > fact.ordering) {
                position = std::min(position, layout->indexOf(it->second.second));
            }
        }

        SectionPickerWidget *sectionPickerWidget = new SectionPickerWidget(fact, model, pageStack);
        
        layout->addSpacing(5);
        layout->addWidget(sectionPickerWidget);

        idSectionPickerMap.insert(std::pair<int, std::pair<Fact, SectionPickerWidget*> >(fact.id, std::pair<Fact, SectionPickerWidget*>(fact, sectionPickerWidget)));

        connect(sectionPickerWidget, SIGNAL(sectionSelected(int)), this, SLOT(sectionSelectedSlot(int)));
    }
}

void SectionPickerWidget::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        sectionLabel->setText(QString::fromStdString(fact.name));
    }
}

void SectionPickerWidget::factDeletedSlot(int id)
{
    if (idSectionPickerMap.count(id) != 0) {
        auto item = idSectionPickerMap.at(id);
        layout->removeWidget(item.second);
        delete item.second;
        idSectionPickerMap.erase(id);
    }
}