#pragma once

#include <QWidget>

#include "database/structures.h"

class ResizableStackedWidget;
class Model;
class ProofForm;
class FormDialog;
class Dialog;
class QLabel;
class Splitter;
class QTextEdit;
class ResizableImage;
class TrafficLight;
class ImageButton;
class BreadCrumbs;
class LatexHighlighter;

class ProofPage : public QWidget
{
    Q_OBJECT

public:
    ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    BreadCrumbs *breadCrumbs;

    ImageButton *editProofButton;
    ProofForm *proofEditForm;
    Dialog *proofEditDialog;

    ImageButton *deleteProofButton;
    Dialog *proofDeleteDialog;

    // Contains the name of the current proof
    QLabel *proofLabel;

    // The splitter
    Splitter *splitter;

    // Contains the current proof's statement
    QTextEdit *bodyTextEdit;
    LatexHighlighter *bodyHighlighter;

    // The rendered statement
    ResizableImage *bodyImage;

    // Shows whether the statement rendered without errors
    TrafficLight *trafficLight;

public slots:
    void proofEditButtonClicked();
    void proofEditDialogCompleted();

    void saveBody();

    void proofDeleteDialogAccepted();

    void proofSelectedChangedSlot(Proof proof);
    void proofEditedSlot(Proof proof);

private:
    void reloadProofDetails(Proof proof);
};