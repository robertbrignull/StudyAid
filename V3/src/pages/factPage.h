#pragma once

#include <iostream>
#include <map>

#include <QWidget>

#include "database/structures.h"

class ResizableStackedWidget;
class Model;
class FactForm;
class FormDialog;
class DeleteDialog;
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
    FormDialog *factEditDialog;

    ImageButton *deleteFactButton;
    DeleteDialog *factDeleteDialog;

    ImageButton *addProofButton;
    FormDialog *proofAddDialog;

    // Contains the name of the current fact
    QLabel *factLabel;

    // The splitter
    Splitter *splitter;

    // Contains the current fact's statement
    QTextEdit *statementTextEdit;

    // The rendered statement
    ResizableImage *statementImage;

    // Shows whether the statement rendered without errors
    TrafficLight *trafficLight;

    // Contains the section on proofs
    QScrollArea *proofsScrollArea;
    QVBoxLayout *proofsScrollLayout;

    // A map from ids to ProofViewWidgets
    std::map<int, std::pair<Proof, ProofViewWidget*> > idProofViewWidgetMap;

public slots:
    void factEditButtonClicked();
    void factEditDialogCompleted(std::map<std::string, std::string> data);

    void saveStatement();

    void factDeleteDialogAccepted();

    void proofAddDialogCompleted(std::map<std::string, std::string> data);

    void factSelectedChangedSlot(Fact fact);
    void factEditedSlot(Fact fact);

    void proofAddedSlot(Proof proof);
    void proofEditedSlot(Proof proof);
    void proofDeletedSlot(int id);

private:
    void insertProofViewWidget(Proof proof, ProofViewWidget *proofViewWidget);
};