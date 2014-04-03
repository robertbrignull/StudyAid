#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QScrollArea>
#include <QTextEdit>
#include <QTimer>

#include "model.h"
#include "database/methods.h"
#include "latex/latex.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/splitter.h"
#include "widgets/resizableImage.h"
#include "widgets/breadCrumbs.h"
#include "widgets/trafficLight.h"
#include "widgets/proofViewWidget.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/factForm.h"
#include "forms/proofForm.h"

#include "pages/factPage.h"

FactPage::FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    factEditForm = new FactForm();
    factEditDialog = new FormDialog(this, factEditForm, "Edit the fact...", "Change");

    factDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this fact?");

    proofAddDialog = new FormDialog(this, new ProofForm(), "Add a new proof...", "Add");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    //  ##   ## #######   ###   #####   ####### #####
    //  ##   ## ##       ## ##  ##  ##  ##      ##  ##
    //  ##   ## ##      ##   ## ##   ## ##      ##   ##
    //  ####### #####   ##   ## ##   ## #####   ##  ##
    //  ##   ## ##      ####### ##   ## ##      #####
    //  ##   ## ##      ##   ## ##  ##  ##      ##  ##
    //  ##   ## ####### ##   ## #####   ####### ##   ##

    // The breadcrumbs show the current course and provide
    // a way to go back to the courses screen.
    // It is presented like a filepath.

    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    BreadCrumbs *breadCrumbs = new BreadCrumbs(2, model, pageStack);
    breadCrumbs->setFixedWidth(700);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(breadCrumbs);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    // Now show the name of the current fact and some buttons to
    // edit it, delete it or add a proof if applicable.

    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    factLabel = new QLabel();
    QFont factFont = factLabel->font();
    factFont.setPointSize(38);
    factLabel->setFont(factFont);

    trafficLight = new TrafficLight(TrafficLight::AMBER);
    trafficLight->setFixedSize(QSize(32, 32));
    QVBoxLayout *trafficLightVLayout = new QVBoxLayout();
    trafficLightVLayout->addSpacing(16);
    trafficLightVLayout->addWidget(trafficLight);

    ImageButton *addProofButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(32, 32));
    QVBoxLayout *addProofVLayout = new QVBoxLayout();
    addProofVLayout->addSpacing(16);
    addProofVLayout->addWidget(addProofButton);

    ImageButton *editFactButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editFactVLayout = new QVBoxLayout();
    editFactVLayout->addSpacing(16);
    editFactVLayout->addWidget(editFactButton);

    ImageButton *deleteFactButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteFactVLayout = new QVBoxLayout();
    deleteFactVLayout->addSpacing(16);
    deleteFactVLayout->addWidget(deleteFactButton);

    topLayout->addWidget(factLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(trafficLightVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(addProofVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(editFactVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteFactVLayout);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);



    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    outerLayout->addSpacing(20);

    

    //  ######   #####  #####   ##    ##
    //  ##   ## ##   ## ##  ###  ##  ##
    //  ##   ## ##   ## ##   ##   ####
    //  ######  ##   ## ##   ##    ##
    //  ##   ## ##   ## ##   ##    ##
    //  ##   ## ##   ## ##  ###    ##
    //  ######   #####  #####      ##

    // Use a vertical splitter to divide the areas.

    Splitter *splitter = new Splitter(Qt::Vertical);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    // The first area is a large text editing widget, this is
    // used to edit the fact's statement.
    // The QTextEdit does its own scrolling.

    statementTextEdit = new QTextEdit();
    QFont font = statementTextEdit->font();
    font.setPointSize(12);
    statementTextEdit->setFont(font);
    splitter->addWidget(statementTextEdit);

    QTimer *statementSaveTimer = new QTimer(this);
    statementSaveTimer->setSingleShot(true);
    statementSaveTimer->setInterval(200);

    connect(statementTextEdit, SIGNAL(textChanged()), statementSaveTimer, SLOT(start()));
    connect(statementSaveTimer, SIGNAL(timeout()), this, SLOT(saveStatement()));



    // The second area contains the rendered statement.

    QScrollArea *statementScrollArea = new QScrollArea();
    statementScrollArea->setWidgetResizable(true);
    statementScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *statementWidget = new QWidget();

    QPalette palette = statementWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    statementWidget->setPalette(palette);
    statementWidget->setAutoFillBackground(true);

    statementImage = new ResizableImage(":/images/default_image.png");

    QHBoxLayout *statementHLayout = new QHBoxLayout();
    statementHLayout->addStretch(1);
    statementHLayout->addWidget(statementImage);
    statementHLayout->addStretch(1);

    QVBoxLayout *statementVLayout = new QVBoxLayout();
    statementVLayout->addLayout(statementHLayout);
    statementVLayout->addStretch(1);

    statementWidget->setLayout(statementVLayout);
    statementScrollArea->setWidget(statementWidget);
    splitter->addWidget(statementScrollArea);



    // The third area shows the proofs for this fact.
    // It shows the rendered proof and buttons to go
    // to the proof page.

    proofsScrollArea = new QScrollArea();
    proofsScrollArea->setWidgetResizable(true);
    proofsScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *proofsWidget = new QWidget();

    palette = proofsWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    proofsWidget->setPalette(palette);
    proofsWidget->setAutoFillBackground(true);

    proofsScrollLayout = new QVBoxLayout();

    idProofViewWidgetMap = std::map<int, std::pair<Proof, ProofViewWidget*> >();

    proofsWidget->setLayout(proofsScrollLayout);
    proofsScrollArea->setWidget(proofsWidget);
    splitter->addWidget(proofsScrollArea);



    //  #####  ####  #####  ##   ##   ###   ##       #####
    // ##   ##  ##  ##   ## ###  ##  ## ##  ##      ##   ##
    //  ##      ##  ##      ###  ## ##   ## ##       ##
    //   ###    ##  ##      ####### ##   ## ##        ###
    //     ##   ##  ##  ### ##  ### ####### ##          ##
    // ##   ##  ##  ##   ## ##  ### ##   ## ##      ##   ##
    //  #####  ####  #####  ##   ## ##   ## #######  #####

    connect(addProofButton, SIGNAL(clicked()), proofAddDialog, SLOT(show()));

    connect(proofAddDialog, SIGNAL(cancelled()), proofAddDialog, SLOT(close()));
    connect(proofAddDialog, SIGNAL(completed(std::map<std::string, std::string>)), this, SLOT(proofAddDialogCompleted(std::map<std::string, std::string>)));

    connect(editFactButton, SIGNAL(clicked()), this, SLOT(factEditButtonClicked()));

    connect(factEditDialog, SIGNAL(cancelled()), factEditDialog, SLOT(close()));
    connect(factEditDialog, SIGNAL(completed(std::map<std::string, std::string>)), this, SLOT(factEditDialogCompleted(std::map<std::string, std::string>)));

    connect(deleteFactButton, SIGNAL(clicked()), factDeleteDialog, SLOT(show()));

    connect(factDeleteDialog, SIGNAL(cancelled()), factDeleteDialog, SLOT(close()));
    connect(factDeleteDialog, SIGNAL(accepted()), this, SLOT(factDeleteDialogAccepted()));

    connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(proofAdded(Proof)), this, SLOT(proofAddedSlot(Proof)));
    connect(model, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
    connect(model, SIGNAL(proofDeleted(int)), this, SLOT(proofDeletedSlot(int)));
}



//   #####  ##       #####  ########  #####
//  ##   ## ##      ##   ##    ##    ##   ##
//   ##     ##      ##   ##    ##     ##
//    ###   ##      ##   ##    ##      ###
//      ##  ##      ##   ##    ##        ##
//  ##   ## ##      ##   ##    ##    ##   ##
//   #####  #######  #####     ##     #####

void FactPage::factEditButtonClicked()
{
    std::map<std::string, std::string> data;
    data.insert(std::pair<std::string, std::string>("type", model->getFactSelected().type));
    data.insert(std::pair<std::string, std::string>("name", model->getFactSelected().name));
    factEditForm->setData(data);

    factEditDialog->show();
}

void FactPage::factEditDialogCompleted(std::map<std::string, std::string> data)
{
    Fact fact = model->getFactSelected();
    fact.type = data.at("type");
    fact.name = data.at("name");
    editFact(fact);

    model->editFact(fact);

    factEditDialog->close();
}

void FactPage::saveStatement()
{
    Fact fact = model->getFactSelected();
    fact.statement = statementTextEdit->toPlainText().toStdString();

    int result = renderFact(fact);

    if (result == 0) {
        statementImage->setImage(getFactImageFilename(fact));
        trafficLight->setState(TrafficLight::GREEN);
    }
    else {
        trafficLight->setState(TrafficLight::RED);
    }

    editFact(fact);
    model->editFact(fact);
}

void FactPage::factDeleteDialogAccepted()
{
    deleteFact(model->getFactSelected().id);

    model->deleteFact(model->getFactSelected().id);

    factDeleteDialog->close();
    pageStack->setCurrentIndex(1);
}

void FactPage::proofAddDialogCompleted(std::map<std::string, std::string> data)
{
    Proof proof = findProof(addProof(model->getFactSelected().id, data.at("name")));

    model->addProof(proof);
    model->setProofSelected(proof);

    proofAddDialog->close();
    pageStack->setCurrentIndex(3);
}

void FactPage::factSelectedChangedSlot(Fact fact)
{
    // Set labels with the name and statement
    factLabel->setText(QString::fromStdString(fact.name));

    if (statementTextEdit->toPlainText() != QString::fromStdString(fact.statement)) {
        statementTextEdit->setPlainText(QString::fromStdString(fact.statement));

        statementImage->setImage(getFactImageFilename(fact));

        trafficLight->setState(TrafficLight::AMBER);
    }

    // Show or hide the proof section depending on fact type
    if (findFactType(fact.type).can_have_proof) {
        // Remove all old proofs
        for (auto it = idProofViewWidgetMap.begin(); it != idProofViewWidgetMap.end(); it++) {
            auto item = it->second;
            proofsScrollLayout->removeWidget(item.second);
            delete item.second;
        }
        idProofViewWidgetMap.clear();

        // Add all proofs of this fact
        std::vector<Proof> proofs = findProofsForFact(fact.id);

        for (size_t i = 0 ; i < proofs.size(); ++i) {
            proofAddedSlot(proofs[i]);
        }

        // Show the section
        proofsScrollArea->show();
    }
    else {
        proofsScrollArea->hide();
    }


}

void FactPage::factEditedSlot(Fact fact)
{
    if (fact.id == model->getFactSelected().id) {
        factSelectedChangedSlot(fact);
    }
}

void FactPage::proofAddedSlot(Proof proof)
{
    insertProofViewWidget(proof, new ProofViewWidget(proof, model, pageStack));
}

void FactPage::proofEditedSlot(Proof proof)
{
    auto item = idProofViewWidgetMap.at(proof.id);

    proofsScrollLayout->removeWidget(item.second);
    idProofViewWidgetMap.erase(proof.id);

    insertProofViewWidget(proof, item.second);
}

void FactPage::proofDeletedSlot(int id)
{
    auto item = idProofViewWidgetMap.at(id);

    proofsScrollLayout->removeWidget(item.second);
    idProofViewWidgetMap.erase(id);
    delete item.second;
}

void FactPage::insertProofViewWidget(Proof proof, ProofViewWidget *proofViewWidget)
{
    int position = idProofViewWidgetMap.size();

    for (auto it = idProofViewWidgetMap.begin(); it != idProofViewWidgetMap.end(); it++) {
        if (it->second.first.ordering > proof.ordering) {
            position = std::min(position, proofsScrollLayout->indexOf(it->second.second));
        }
    }

    proofsScrollLayout->insertWidget(position, proofViewWidget);

    idProofViewWidgetMap.insert(std::pair<int, std::pair<Proof, ProofViewWidget*> >(proof.id, std::pair<Proof, ProofViewWidget*>(proof, proofViewWidget)));
}