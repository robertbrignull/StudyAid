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
class QTimer;
class LatexHighlighter;
class QPushButton;

class ProofPage : public QWidget
{
    Q_OBJECT

public:
    ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    QPushButton *newWindowButton;

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

    // Contains the current proof's body
    QTextEdit *bodyTextEdit;
    LatexHighlighter *bodyHighlighter;

    // For the timer that saves and renders the body
    QTimer *bodySaveTimer;

    // The rendered body
    ResizableImage *bodyImage;

    // Shows whether the body rendered without errors
    TrafficLight *trafficLight;

signals:
    void requestNewWindow(int pageIndex, Course course, Fact fact, Proof proof);

public slots:
    void proofEditButtonClicked();
    void proofEditDialogCompleted();

    void bodyChanged();
    void saveBody();

    void proofDeleteDialogAccepted();

    void newWindowButtonClicked();

    void proofSelectedChangedSlot(Proof proof);
    void proofEditedSlot(Proof proof);
    void proofRenderedSlot(Proof proof, bool success);
    void proofDeletedSlot(int id);

private:
    void reloadProofDetails(Proof proof);
};