#include <iostream>

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
#include "views/dependenciesWidget.h"
#include "views/breadCrumbs.h"
#include "views/latexHighlighter.h"
#include "forms/proofForm.h"

#include "pages/proofPage.h"

ProofPage::ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    proofEditForm = new ProofForm();
    proofEditDialog = new Dialog(this, proofEditForm, "Edit the proof...", "Change", "Cancel");

    proofDeleteDialog = new Dialog(this, nullptr, "Are you sure you want to delete this proof?", "Delete", "Cancel");



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

    breadCrumbs = new BreadCrumbs(3, model, pageStack);
    breadCrumbs->setFixedWidth(700);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(breadCrumbs);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    // Now show the name of the current proof and some buttons to
    // edit it, delete it or add a new dependency.

    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    proofLabel = new QLabel();
    proofLabel->setWordWrap(true);
    proofLabel->setScaledContents(true);

    QFont proofFont = proofLabel->font();
    proofFont.setPointSize(24);
    proofLabel->setFont(proofFont);

    trafficLight = new TrafficLight(TrafficLight::AMBER);
    trafficLight->setFixedSize(QSize(32, 32));
    QVBoxLayout *trafficLightVLayout = new QVBoxLayout();
    trafficLightVLayout->addSpacing(16);
    trafficLightVLayout->addWidget(trafficLight);

    newWindowButton = new ImageButton(QPixmap(":/images/open_window_black.png"), QSize(32, 32));
    QVBoxLayout *newWindowVLayout = new QVBoxLayout();
    newWindowVLayout->addSpacing(16);
    newWindowVLayout->addWidget(newWindowButton);

    editProofButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editProofVLayout = new QVBoxLayout();
    editProofVLayout->addSpacing(16);
    editProofVLayout->addWidget(editProofButton);

    deleteProofButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteProofVLayout = new QVBoxLayout();
    deleteProofVLayout->addSpacing(16);
    deleteProofVLayout->addWidget(deleteProofButton);

    topLayout->addWidget(proofLabel);
    topLayout->addLayout(newWindowVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(trafficLightVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(editProofVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteProofVLayout);

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



    // The first area contains the rendered statement.

    QScrollArea *statementScrollArea = new QScrollArea();
    statementScrollArea->setWidgetResizable(true);
    statementScrollArea->setFrameShape(QFrame::NoFrame);

    statementImage = new ResizableImage("");

    statementScrollArea->setWidget(statementImage);
    splitter->addWidget(statementScrollArea);




    // The second area is a large text editing widget, this is
    // used to edit the proof's body.
    // The QTextEdit does its own scrolling.

    bodyTextEdit = new QTextEdit();

    QFont font = bodyTextEdit->font();
    font.setFamily("Courier");
    font.setPointSize(12);
    bodyTextEdit->setFont(font);

    bodyHighlighter = new LatexHighlighter(bodyTextEdit->document());

    splitter->addWidget(bodyTextEdit);

    bodySaveTimer = new QTimer(this);
    bodySaveTimer->setSingleShot(true);
    bodySaveTimer->setInterval(200);

    connect(bodyTextEdit, SIGNAL(textChanged()), this, SLOT(bodyChanged()));
    connect(bodySaveTimer, SIGNAL(timeout()), this, SLOT(saveBody()));



    // The third area contains the rendered body.

    QScrollArea *bodyScrollArea = new QScrollArea();
    bodyScrollArea->setWidgetResizable(true);
    bodyScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *bodyWidget = new QWidget();

    QPalette palette = bodyWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    bodyWidget->setPalette(palette);
    bodyWidget->setAutoFillBackground(true);

    bodyImage = new ResizableImage("");
    
    bodyScrollArea->setWidget(bodyImage);
    splitter->addWidget(bodyScrollArea);



    //  #####  ####  #####  ##   ##   ###   ##       #####
    // ##   ##  ##  ##   ## ###  ##  ## ##  ##      ##   ##
    //  ##      ##  ##      ###  ## ##   ## ##       ##
    //   ###    ##  ##      ####### ##   ## ##        ###
    //     ##   ##  ##  ### ##  ### ####### ##          ##
    // ##   ##  ##  ##   ## ##  ### ##   ## ##      ##   ##
    //  #####  ####  #####  ##   ## ##   ## #######  #####

    connect(editProofButton, SIGNAL(clicked()), this, SLOT(proofEditButtonClicked()));

    connect(proofEditDialog, SIGNAL(accepted()), this, SLOT(proofEditDialogCompleted()));
    connect(proofEditDialog, SIGNAL(rejected()), proofEditDialog, SLOT(close()));

    connect(deleteProofButton, SIGNAL(clicked()), proofDeleteDialog, SLOT(show()));

    connect(proofDeleteDialog, SIGNAL(accepted()), this, SLOT(proofDeleteDialogAccepted()));
    connect(proofDeleteDialog, SIGNAL(rejected()), proofDeleteDialog, SLOT(close()));

    connect(newWindowButton, SIGNAL(clicked()), this, SLOT(newWindowButtonClicked()));

    connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
    connect(model, SIGNAL(factRendered(Fact, bool)), this, SLOT(factRenderedSlot(Fact, bool)));

    connect(model, SIGNAL(proofSelectedChanged(Proof)), this, SLOT(proofSelectedChangedSlot(Proof)));
    connect(model, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
    connect(model, SIGNAL(proofRendered(Proof, bool)), this, SLOT(proofRenderedSlot(Proof, bool)));
    connect(model, SIGNAL(proofDeleted(int)), this, SLOT(proofDeletedSlot(int)));
}



//   #####  ##       #####  ########  #####
//  ##   ## ##      ##   ##    ##    ##   ##
//   ##     ##      ##   ##    ##     ##
//    ###   ##      ##   ##    ##      ###
//      ##  ##      ##   ##    ##        ##
//  ##   ## ##      ##   ##    ##    ##   ##
//   #####  #######  #####     ##     #####

void ProofPage::proofEditButtonClicked()
{
    proofEditDialog->show();
    proofEditForm->setData(model->getProofSelected());
}

void ProofPage::proofEditDialogCompleted()
{
    Proof proof = proofEditForm->getData();

    model->editProof(proof);

    proofEditDialog->close();
}

void ProofPage::bodyChanged()
{
    if (model->isProofSelected() && !bodySaveTimer->isActive()) {
        saveBody();

        bodySaveTimer->start();
    }
}

void ProofPage::saveBody()
{
    Proof proof = model->getProofSelected();
    proof.body = bodyTextEdit->toPlainText().toStdString();

    model->editProof(proof);
    model->renderProof(proof);
}

void ProofPage::proofDeleteDialogAccepted()
{
    proofDeleteDialog->close();
    
    model->deleteProof(model->getProofSelected().id);
}

void ProofPage::newWindowButtonClicked()
{
    emit requestNewWindow(pageStack->currentIndex(), model->getCourseSelected(), model->getFactSelected(), model->getProofSelected());
}

void ProofPage::factSelectedChangedSlot(Fact fact)
{
    statementImage->setImage(getFactImageFilename(fact));
}

void ProofPage::factRenderedSlot(Fact fact, bool success)
{
    if (fact.id == model->getProofSelected().fact && success) {
        statementImage->setImage(getFactImageFilename(fact));
    }
}

void ProofPage::proofSelectedChangedSlot(Proof proof)
{
    reloadProofDetails(proof);

    if (proof.body == "") {
        splitter->setSizes({ 0, 1, 1, 0 });
    }
    else {
        splitter->setSizes({ 0, 0, 1, 0 });
    }
}

void ProofPage::proofEditedSlot(Proof proof)
{
    reloadProofDetails(proof);
}

void ProofPage::proofRenderedSlot(Proof proof, bool success)
{
    if (proof.id == model->getProofSelected().id) {
        bodyImage->setImage(getProofImageFilename(proof));
        
        if (success) {
            trafficLight->setState(TrafficLight::GREEN);
        }
        else {
            trafficLight->setState(TrafficLight::RED);
        }
    }
}

void ProofPage::proofDeletedSlot(int id)
{
    if (id == model->getProofSelected().id && pageStack->currentIndex() > 2) {
        pageStack->setCurrentIndex(2);
    }
}

//  ##      ## ####### ######## ##    ##  #####  #####    #####
//  ###    ### ##         ##    ##    ## ##   ## ##  ### ##   ##
//  ####  #### ##         ##    ##    ## ##   ## ##   ##  ##
//  ## #### ## #####      ##    ######## ##   ## ##   ##   ###
//  ##  ##  ## ##         ##    ##    ## ##   ## ##   ##     ##
//  ##      ## ##         ##    ##    ## ##   ## ##  ### ##   ##
//  ##      ## #######    ##    ##    ##  #####  #####    #####

void ProofPage::reloadProofDetails(Proof proof)
{
    // Set labels with the proof and body
    proofLabel->setText((proof.name != "") ? QString::fromStdString(proof.name) : "Proof");

    if (bodyTextEdit->toPlainText() != QString::fromStdString(proof.body)) {
        bodyTextEdit->setPlainText(QString::fromStdString(proof.body));

        bodyImage->setImage(getProofImageFilename(proof));

        trafficLight->setState(TrafficLight::AMBER);
    }
}