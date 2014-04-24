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
#include "widgets/trafficLight.h"
#include "widgets/dialog.h"
#include "views/breadCrumbs.h"
#include "views/proofViewWidget.h"
#include "views/latexHighlighter.h"
#include "forms/factForm.h"
#include "forms/proofForm.h"

#include "pages/factPage.h"

FactPage::FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    factEditForm = new FactForm();
    factEditDialog = new Dialog(this, factEditForm, "Edit the fact...", "Change", "Cancel");

    factDeleteDialog = new Dialog(this, nullptr, "Are you sure you want to delete this fact?", "Delete", "Cancel");

    proofAddForm = new ProofForm();
    proofAddDialog = new Dialog(this, proofAddForm, "Add a new proof...", "Add", "Cancel");



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

    breadCrumbs = new BreadCrumbs(2, model, pageStack);
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
    factLabel->setWordWrap(true);
    factLabel->setScaledContents(true);

    QFont factFont = factLabel->font();
    factFont.setPointSize(24);
    factLabel->setFont(factFont);

    trafficLight = new TrafficLight(TrafficLight::AMBER);
    trafficLight->setFixedSize(QSize(32, 32));
    QVBoxLayout *trafficLightVLayout = new QVBoxLayout();
    trafficLightVLayout->addSpacing(16);
    trafficLightVLayout->addWidget(trafficLight);

    addProofButton = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(32, 32));
    QVBoxLayout *addProofVLayout = new QVBoxLayout();
    addProofVLayout->addSpacing(16);
    addProofVLayout->addWidget(addProofButton);

    editFactButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editFactVLayout = new QVBoxLayout();
    editFactVLayout->addSpacing(16);
    editFactVLayout->addWidget(editFactButton);

    deleteFactButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteFactVLayout = new QVBoxLayout();
    deleteFactVLayout->addSpacing(16);
    deleteFactVLayout->addWidget(deleteFactButton);

    topLayout->addWidget(factLabel);
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

    splitter = new Splitter(Qt::Vertical);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    // The first area is a large text editing widget, this is
    // used to edit the fact's statement.
    // The QTextEdit does its own scrolling.

    statementTextEdit = new QTextEdit();

    QFont font = statementTextEdit->font();
    font.setFamily("Courier");
    font.setPointSize(12);
    statementTextEdit->setFont(font);

    statementHighlighter = new LatexHighlighter(statementTextEdit->document());

    splitter->addWidget(statementTextEdit);

    statementSaveTimer = new QTimer(this);
    statementSaveTimer->setSingleShot(true);
    statementSaveTimer->setInterval(200);

    connect(statementTextEdit, SIGNAL(textChanged()), this, SLOT(statementChanged()));
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

    statementImage = new ResizableImage("");

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
    proofsScrollLayout->addStretch(1);

    idProofViewWidgetMap = std::map<int, ProofViewWidget*>();

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

    connect(proofAddDialog, SIGNAL(accepted()), this, SLOT(proofAddDialogCompleted()));
    connect(proofAddDialog, SIGNAL(rejected()), proofAddDialog, SLOT(close()));

    connect(editFactButton, SIGNAL(clicked()), this, SLOT(factEditButtonClicked()));

    connect(factEditDialog, SIGNAL(accepted()), this, SLOT(factEditDialogCompleted()));
    connect(factEditDialog, SIGNAL(rejected()), factEditDialog, SLOT(close()));

    connect(deleteFactButton, SIGNAL(clicked()), factDeleteDialog, SLOT(show()));

    connect(factDeleteDialog, SIGNAL(accepted()), this, SLOT(factDeleteDialogAccepted()));
    connect(factDeleteDialog, SIGNAL(rejected()), factDeleteDialog, SLOT(close()));

    connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factRendered(Fact, bool)), this, SLOT(factRenderedSlot(Fact, bool)));
    connect(model, SIGNAL(factDeleted(int)), this, SLOT(factDeletedSlot(int)));
    connect(model, SIGNAL(proofAdded(Proof)), this, SLOT(proofAddedSlot(Proof)));
    connect(model, SIGNAL(proofOrderingEdited(Proof)), this, SLOT(proofOrderingEditedSlot(Proof)));
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
    factEditDialog->show();
    factEditForm->setData(model->getFactSelected());
}

void FactPage::factEditDialogCompleted()
{
    Fact fact = factEditForm->getData();

    editFact(fact);
    model->editFact(fact);

    factEditDialog->close();
}

void FactPage::statementChanged()
{
    if (model->isFactSelected() && !statementSaveTimer->isActive()) {
        saveStatement();

        statementSaveTimer->start();
    }
}

void FactPage::saveStatement()
{
    Fact fact = model->getFactSelected();
    fact.statement = statementTextEdit->toPlainText().toStdString();

    editFact(fact);
    model->editFact(fact);

    renderFact(fact);
}

void FactPage::factDeleteDialogAccepted()
{
    factDeleteDialog->close();
    
    deleteFact(model->getFactSelected().id);
    model->deleteFact(model->getFactSelected().id);
}

void FactPage::proofAddDialogCompleted()
{
    Proof proof = findProof(addProof(model->getFactSelected().id, proofAddForm->getData().name));

    model->addProof(proof);
    model->setProofSelected(proof);

    proofAddDialog->close();
    pageStack->setCurrentIndex(3);
}

void FactPage::factSelectedChangedSlot(Fact fact)
{
    reloadFactDetails(fact);

    if (fact.statement == "") {
        splitter->setSizes({ 1, 1, 0 });
    }
    else {
        splitter->setSizes({ 0, 1, 0 });
    }
}

void FactPage::factEditedSlot(Fact fact)
{
    if (fact.id == model->getFactSelected().id) {
        reloadFactDetails(fact);
    }
}

void FactPage::factRenderedSlot(Fact fact, bool success)
{
    if (fact.id == model->getFactSelected().id) {
        statementImage->setImage(getFactImageFilename(fact));
        
        if (success) {
            trafficLight->setState(TrafficLight::GREEN);
        }
        else {
            trafficLight->setState(TrafficLight::RED);
        }
    }
}

void FactPage::factDeletedSlot(int id)
{
    if (id == model->getFactSelected().id && pageStack->currentIndex() > 1) {
        pageStack->setCurrentIndex(1);
    }
}

void FactPage::proofAddedSlot(Proof proof)
{
    insertProofViewWidget(new ProofViewWidget(proof, model, pageStack));
}

void FactPage::proofOrderingEditedSlot(Proof proof)
{
    // Update orderings on children
    for (auto it = idProofViewWidgetMap.begin(); it != idProofViewWidgetMap.end(); it++) {
        if (it->second->proof.id == proof.id) {
            it->second->proof = proof;
        }
        else if (it->second->proof.ordering >= proof.ordering) {
            it->second->proof.ordering += 1;
        }
    }

    // Remove the edited ProofViewWidget and re-add it
    ProofViewWidget *proofViewWidget = idProofViewWidgetMap.at(proof.id);

    proofsScrollLayout->removeWidget(proofViewWidget);
    idProofViewWidgetMap.erase(proof.id);

    insertProofViewWidget(proofViewWidget);
}

void FactPage::proofDeletedSlot(int id)
{
    auto item = idProofViewWidgetMap.at(id);

    proofsScrollLayout->removeWidget(item);
    idProofViewWidgetMap.erase(id);
    delete item;
}

//  ##      ## ####### ######## ##    ##  #####  #####    #####
//  ###    ### ##         ##    ##    ## ##   ## ##  ### ##   ##
//  ####  #### ##         ##    ##    ## ##   ## ##   ##  ##
//  ## #### ## #####      ##    ######## ##   ## ##   ##   ###
//  ##  ##  ## ##         ##    ##    ## ##   ## ##   ##     ##
//  ##      ## ##         ##    ##    ## ##   ## ##  ### ##   ##
//  ##      ## #######    ##    ##    ##  #####  #####    #####

void FactPage::insertProofViewWidget(ProofViewWidget *proofViewWidget)
{
    int position = idProofViewWidgetMap.size();

    for (auto it = idProofViewWidgetMap.begin(); it != idProofViewWidgetMap.end(); it++) {
        if (it->second->proof.ordering > proofViewWidget->proof.ordering) {
            position = std::min(position, proofsScrollLayout->indexOf(it->second));
        }
    }

    proofsScrollLayout->insertWidget(position, proofViewWidget);

    idProofViewWidgetMap.insert(std::pair<int, ProofViewWidget*>(proofViewWidget->proof.id, proofViewWidget));

    connect(proofViewWidget, SIGNAL(moveButtonClicked(Proof)), this, SIGNAL(moveButtonClicked(Proof)));
    connect(proofViewWidget, SIGNAL(moveCompleted()), this, SIGNAL(moveCompleted()));

    connect(this, SIGNAL(moveButtonClicked(Proof)), proofViewWidget, SLOT(activateMoveMode(Proof)));
    connect(this, SIGNAL(moveCompleted()), proofViewWidget, SLOT(deactivateMoveMode()));
}

void FactPage::reloadFactDetails(Fact fact)
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
            proofsScrollLayout->removeWidget(it->second);
            delete it->second;
        }
        idProofViewWidgetMap.clear();

        // Add all proofs of this fact
        std::vector<Proof> proofs = findProofsForFact(fact.id);

        for (size_t i = 0 ; i < proofs.size(); ++i) {
            proofAddedSlot(proofs[i]);
        }

        // Show the section
        proofsScrollArea->show();
        addProofButton->show();
    }
    else {
        proofsScrollArea->hide();
        addProofButton->hide();
    }
}