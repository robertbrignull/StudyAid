#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "model.h"
#include "latex/latex.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"

#include "views/proofViewWidget.h"

ProofViewWidget::ProofViewWidget(Proof proof, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->proof = proof;
    this->model = model;
    this->pageStack = pageStack;



    QVBoxLayout *outerLayout = new QVBoxLayout(this);

    viewProofButton = new ImageButton(QPixmap(":/images/arrow_right_black.png"), QSize(24, 24));
    nameLabel = new QLabel(QString::fromStdString(proof.name));

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(nameLabel);
    topLayout->addStretch(1);
    topLayout->addWidget(viewProofButton);
    outerLayout->addLayout(topLayout);

    bodyImage = new ResizableImage(getProofImageFilename(proof));

    QHBoxLayout *bodyLayout = new QHBoxLayout();
    bodyLayout->addStretch(1);
    bodyLayout->addWidget(bodyImage);
    bodyLayout->addStretch(1);
    outerLayout->addLayout(bodyLayout);



    connect(viewProofButton, SIGNAL(clicked()), this, SLOT(viewProofButtonClicked()));
    connect(model, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
}

void ProofViewWidget::viewProofButtonClicked()
{
    model->setProofSelected(proof);
    pageStack->setCurrentIndex(3);
}

void ProofViewWidget::proofEditedSlot(Proof proof)
{
    if (proof.id == this->proof.id) {
        this->proof = proof;

        nameLabel->setText(QString::fromStdString(proof.name));
        bodyImage->reloadImage();
    }
}