#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "model.h"
#include "latex/latex.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"
#include "database/methods.h"

#include "views/proofViewWidget.h"

ProofViewWidget::ProofViewWidget(Proof proof, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->proof = proof;
    this->model = model;
    this->pageStack = pageStack;



    QVBoxLayout *outerLayout = new QVBoxLayout(this);

    nameLabel = new QLabel((proof.name != "") ? QString::fromStdString(proof.name) : "Proof");

    viewProofButton = new ImageButton(QPixmap(":/images/arrow_right_black.png"), QSize(24, 24));

    moveButton = new ImageButton(QPixmap(":/images/move_black.png"), QSize(24, 24));
    moveAboveButton = new ImageButton(QPixmap(":/images/arrow_up_black.png"), QSize(24, 24));
    moveBelowButton = new ImageButton(QPixmap(":/images/arrow_down_black.png"), QSize(24, 24));

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(nameLabel);
    topLayout->addStretch(1);
    topLayout->addWidget(moveBelowButton);
    topLayout->addWidget(moveAboveButton);
    topLayout->addWidget(moveButton);
    topLayout->addWidget(viewProofButton);
    outerLayout->addLayout(topLayout);

    bodyImage = new ResizableImage(getProofImageFilename(proof));

    QHBoxLayout *bodyLayout = new QHBoxLayout();
    bodyLayout->addStretch(1);
    bodyLayout->addWidget(bodyImage);
    bodyLayout->addStretch(1);
    outerLayout->addLayout(bodyLayout);



    deactivateMoveMode();



    connect(viewProofButton, SIGNAL(clicked()), this, SLOT(viewProofButtonClicked()));

    connect(moveButton, SIGNAL(clicked()), this, SLOT(moveButtonClickedSlot()));
    connect(moveAboveButton, SIGNAL(clicked()), this, SLOT(moveAboveButtonClickedSlot()));
    connect(moveBelowButton, SIGNAL(clicked()), this, SLOT(moveBelowButtonClickedSlot()));

    connect(model, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
}

void ProofViewWidget::viewProofButtonClicked()
{
    model->setProofSelected(proof);
    pageStack->setCurrentIndex(3);
}

void ProofViewWidget::moveButtonClickedSlot()
{
    if (inMoveMode) {
        emit moveCompleted();
    }
    else {
        emit moveButtonClicked(proof);
    }
}

void ProofViewWidget::moveAboveButtonClickedSlot()
{
    moveProof.ordering = proof.ordering;

    editProofOrdering(moveProof);
    model->editProofOrdering(moveProof);

    emit moveCompleted();
}

void ProofViewWidget::moveBelowButtonClickedSlot()
{
    moveProof.ordering = proof.ordering + 1;

    editProofOrdering(moveProof);
    model->editProofOrdering(moveProof);

    emit moveCompleted();
}

void ProofViewWidget::activateMoveMode(Proof proof)
{
    inMoveMode = true;
    moveProof = proof;

    if (proof.id == this->proof.id) {
        viewProofButton->hide();
        moveButton->show();
        moveAboveButton->hide();
        moveBelowButton->hide();
    }
    else {
        viewProofButton->hide();
        moveButton->hide();
        moveAboveButton->show();
        moveBelowButton->show();
    }
}

void ProofViewWidget::deactivateMoveMode()
{
    inMoveMode = false;

    viewProofButton->show();
    moveButton->show();
    moveAboveButton->hide();
    moveBelowButton->hide();
}

void ProofViewWidget::proofEditedSlot(Proof proof)
{
    if (proof.id == this->proof.id) {
        this->proof = proof;

        nameLabel->setText((proof.name != "") ? QString::fromStdString(proof.name) : "Proof");
    }
}

void ProofViewWidget::proofRenderedSlot(Proof proof, bool success)
{
    if (proof.id == this->proof.id && success) {
        this->proof = proof;

        bodyImage->reloadImage();
    }
}