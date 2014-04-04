#pragma once

#include <QWidget>

#include "database/structures.h"

class ResizableStackedWidget;
class Model;
class ProofForm;
class FormDialog;
class DeleteDialog;
class QLabel;
class Splitter;
class QTextEdit;
class ResizableImage;
class TrafficLight;

class ProofPage : public QWidget
{
    Q_OBJECT

public:
    ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

public slots:
    void proofEditButtonClicked();
    void proofEditDialogCompleted(std::map<std::string, std::string> data);

    void saveBody();

    void proofDeleteDialogAccepted();

    void proofSelectedChangedSlot(Proof proof);
    void proofEditedSlot(Proof proof);

private:
    Model *model;
    ResizableStackedWidget *pageStack;

    // The form and dialog for editing a proof
    ProofForm *proofEditForm;
    FormDialog *proofEditDialog;

    // Dialog for deleting a proof
    DeleteDialog *proofDeleteDialog;

    // Contains the name of the current proof
    QLabel *proofLabel;

    // The splitter
    Splitter *splitter;

    // Contains the current proof's statement
    QTextEdit *bodyTextEdit;

    // The rendered statement
    ResizableImage *bodyImage;

    // Shows whether the statement rendered without errors
    TrafficLight *trafficLight;
};