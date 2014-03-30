#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "database/methods.h"
#include "widgets/clickableQLabel.h"
#include "widgets/imageButton.h"
#include "dialogs/formDialog.h"
#include "forms/factForm.h"

#include "widgets/sectionPickerWidget.h"

SectionPickerWidget::SectionPickerWidget(int id, std::string name, QWidget *parent)
    : QWidget(parent)
{
    FormDialog *factAddDialog = new FormDialog(this, new FactForm(), "Add a new fact...", "Add");

    QVBoxLayout *layout = new QVBoxLayout(this);



    QHBoxLayout *sectionLayout = new QHBoxLayout();
    ClickableQLabel *sectionLabel = new ClickableQLabel(name);
    ImageButton *viewSectionButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(16, 16));

    sectionLayout->addWidget(sectionLabel);
    sectionLayout->addStretch(1);
    sectionLayout->addWidget(viewSectionButton);

    layout->addLayout(sectionLayout);

    connect(sectionLabel, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(id);
    });

    connect(viewSectionButton, &ImageButton::clicked, [=](){
        factAddDialog->show();
    });

    connect(factAddDialog, &FormDialog::cancelled, [=](){
        factAddDialog->close();
    });

    connect(factAddDialog, &FormDialog::completed, [=](std::map<std::string, std::string> data){
        Fact fact = findFact(addFact(id, data.at("name"), data.at("type")));
        factAddDialog->close();
        emit factAdded(fact);
    });



    std::vector<Fact> facts = findChildSections(id);

    for (size_t i = 0; i < facts.size(); ++i) {
        SectionPickerWidget *sectionPickerWidget = new SectionPickerWidget(facts[i].id, facts[i].name);

        layout->addWidget(sectionPickerWidget);

        connect(sectionPickerWidget, &SectionPickerWidget::sectionSelected, [=](int id){
            emit sectionSelected(id);
        });

        connect(sectionPickerWidget, &SectionPickerWidget::factAdded, [=](Fact fact){
            emit factAdded(fact);
        });
    }
}