#pragma once

#include <QWidget>

#include "database/structures.h"

class Model;
class ResizableStackedWidget;
class ImageButton;
class ResizableImage;
class QLabel;

class ProofViewWidget : public QWidget
{
    Q_OBJECT

public:
    ProofViewWidget(Proof proof, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);


    
    Proof proof;
    Model *model;
    ResizableStackedWidget *pageStack;

    ImageButton *viewProofButton;
    ResizableImage *bodyImage;
    QLabel *nameLabel;

    Proof moveProof;
    ImageButton *moveButton, *moveAboveButton, *moveBelowButton;
    bool inMoveMode;

signals:
    void moveButtonClicked(Proof proof);
    void moveCompleted();

public slots:
    void viewProofButtonClicked();

    void moveButtonClickedSlot();
    void moveAboveButtonClickedSlot();
    void moveBelowButtonClickedSlot();

    void activateMoveMode(Proof proof);
    void deactivateMoveMode();

    void proofEditedSlot(Proof proof);
};