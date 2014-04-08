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

SectionPickerWidget::SectionPickerWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactForm *factAddForm, Dialog *factAddDialog, FactForm *sectionEditForm, Dialog *sectionEditDialog, QWidget *parent)
    : QWidget(parent)
{
    this->fact = fact;
    this->model = model;
    this->pageStack = pageStack;

    this->factAddForm = factAddForm;
    this->factAddDialog = factAddDialog;

    this->sectionEditForm = sectionEditForm;
    this->sectionEditDialog = sectionEditDialog;



    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);



    QHBoxLayout *sectionLayout = new QHBoxLayout();
    sectionLabel = new ClickableQLabel((fact.parent != -1) ? fact.name : "All");

    sectionLayout->addWidget(sectionLabel);
    sectionLayout->addStretch(1);

    if (fact.parent != -1) {
        deleteSectionButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(16, 16));
        sectionLayout->addWidget(deleteSectionButton);

        sectionDeleteDialog = new Dialog(this, nullptr, "Are you sure you want to delete this section?", "Delete", "Cancel");

        editSectionButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(16, 16));
        sectionLayout->addWidget(editSectionButton);
    }

    addFactButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(16, 16));
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

    connect(addFactButton, SIGNAL(clicked()), this, SLOT(factAddButtonClicked()));

    if (fact.parent != -1) {
        connect(deleteSectionButton, SIGNAL(clicked()), sectionDeleteDialog, SLOT(show()));

        connect(sectionDeleteDialog, SIGNAL(cancelled()), sectionDeleteDialog, SLOT(close()));
        connect(sectionDeleteDialog, SIGNAL(completed()), this, SLOT(sectionDeleteDialogAccepted()));

        connect(editSectionButton, SIGNAL(clicked()), this, SLOT(sectionEditButtonClicked()));
    }

    connect(model, SIGNAL(factAdded(Fact)), this, SLOT(factAddedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));
}

void SectionPickerWidget::sectionSelectedSlot(int id)
{
    emit sectionSelected(id);
}

void SectionPickerWidget::factAddButtonClicked()
{
    Fact newFact = Fact();
    newFact.parent = fact.id;

    factAddForm->setData(newFact);

    factAddDialog->show();
}

void SectionPickerWidget::sectionEditButtonClicked()
{
    sectionEditForm->setData(fact);

    sectionEditDialog->show();
}

void SectionPickerWidget::sectionDeleteDialogAccepted()
{
    sectionDeleteDialog->close();
    
    deleteFact(fact.id);
    model->deleteFact(fact.id);
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

        SectionPickerWidget *sectionPickerWidget = new SectionPickerWidget(fact, model, pageStack, factAddForm, factAddDialog, sectionEditForm, sectionEditDialog);
        
        layout->addSpacing(5);
        layout->addWidget(sectionPickerWidget);

        idSectionPickerMap.insert(std::pair<int, std::pair<Fact, SectionPickerWidget*> >(fact.id, std::pair<Fact, SectionPickerWidget*>(fact, sectionPickerWidget)));

        connect(sectionPickerWidget, SIGNAL(sectionSelected(int)), this, SLOT(sectionSelectedSlot(int)));
    }
}

void SectionPickerWidget::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
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