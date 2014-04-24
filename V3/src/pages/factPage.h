#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class ResizableStackedWidget;
class Model;
class FactForm;
class ProofForm;
class Dialog;
class ClickableQLabel;
class QLabel;
class Splitter;
class QTextEdit;
class QVBoxLayout;
class ResizableImage;
class TrafficLight;
class QScrollArea;
class ProofViewWidget;
class ImageButton;
class BreadCrumbs;
class QTimer;
class LatexHighlighter;

class FactPage : public QWidget
{
    Q_OBJECT

public:
    FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    BreadCrumbs *breadCrumbs;

    ImageButton *editFactButton;
    FactForm *factEditForm;
    Dialog *factEditDialog;

    ImageButton *deleteFactButton;
    Dialog *factDeleteDialog;

    ImageButton *addProofButton;
    ProofForm *proofAddForm;
    Dialog *proofAddDialog;

    // Contains the name of the current fact
    QLabel *factLabel;

    // The splitter
    Splitter *splitter;

    // Contains the current fact's statement
    QTextEdit *statementTextEdit;
    LatexHighlighter *statementHighlighter;

    // For the timer that saves and renders the statement
    QTimer *statementSaveTimer;

    // The rendered statement
    ResizableImage *statementImage;

    // Shows whether the statement rendered without errors
    TrafficLight *trafficLight;

    // Contains the section on proofs
    QScrollArea *proofsScrollArea;
    QVBoxLayout *proofsScrollLayout;

    // A map from ids to ProofViewWidgets
    std::map<int, ProofViewWidget*> idProofViewWidgetMap;

signals:
    void moveButtonClicked(Proof proof);
    void moveCompleted();

public slots:
    void factEditButtonClicked();
    void factEditDialogCompleted();

    void statementChanged();
    void saveStatement();

    void factDeleteDialogAccepted();

    void proofAddDialogCompleted();

    void factSelectedChangedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factRenderedSlot(Fact fact, bool success);
    void factDeletedSlot(int id);

    void proofAddedSlot(Proof proof);
    void proofOrderingEditedSlot(Proof proof);
    void proofDeletedSlot(int id);

private:
    void insertProofViewWidget(ProofViewWidget *proofViewWidget);

    void reloadFactDetails(Fact fact);
};