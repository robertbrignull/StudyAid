#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>

#include "model.h"
#include "database/methods.h"
#include "widgets/clickableQLabel.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/dialog.h"
#include "forms/factForm.h"
#include "forms/sectionForm.h"

#include "views/sectionPickerWidget.h"

SectionPickerWidget::SectionPickerWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactForm *factAddForm, Dialog *factAddDialog, SectionForm *sectionEditForm, Dialog *sectionEditDialog, QWidget *parent)
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
    layout->setContentsMargins(6, 0, 0, 5);



    QHBoxLayout *sectionLayout = new QHBoxLayout();
    sectionLabel = new ClickableQLabel((fact.parent != -1) ? QString::fromStdString(fact.name) : "All");

    sectionLabel->setWordWrap(true);
    sectionLabel->setScaledContents(true);

    sectionLayout->addWidget(sectionLabel);

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
    idSectionPickerMap = std::map<int, SectionPickerWidget*>();

    for (size_t i = 0; i < facts.size(); ++i) {
        factAddedSlot(facts[i]);
    }



    connect(sectionLabel, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(fact.id);
    });

    connect(addFactButton, SIGNAL(clicked()), this, SLOT(factAddButtonClicked()));

    if (fact.parent != -1) {
        connect(deleteSectionButton, SIGNAL(clicked()), sectionDeleteDialog, SLOT(show()));

        connect(sectionDeleteDialog, SIGNAL(accepted()), this, SLOT(sectionDeleteDialogAccepted()));
        connect(sectionDeleteDialog, SIGNAL(rejected()), sectionDeleteDialog, SLOT(close()));

        connect(editSectionButton, SIGNAL(clicked()), this, SLOT(sectionEditButtonClicked()));
    }

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
        insertSectionPickerWidget(new SectionPickerWidget(fact, model, pageStack, factAddForm, factAddDialog, sectionEditForm, sectionEditDialog));
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

        insertSectionPickerWidget(new SectionPickerWidget(fact, model, pageStack, factAddForm, factAddDialog, sectionEditForm, sectionEditDialog));
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