#pragma once

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
class QScrollArea;
class ResizableImage;
class TrafficLight;

class FactPage : public QWidget
{
    Q_OBJECT

public:
    FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

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
    Model *model;
    ResizableStackedWidget *pageStack;

    // The form and dialog for editing a fact
    FactForm *factEditForm;
    FormDialog *factEditDialog;

    // Dialog for deleting a fact
    DeleteDialog *factDeleteDialog;

    // Dialog for adding a proof
    FormDialog *proofAddDialog;

    // Contains the name of the current fact
    QLabel *factLabel;

    // Contains the current fact's statement
    QTextEdit *statementTextEdit;

    // The rendered statement
    ResizableImage *statementImage;

    // Shows whether the statement rendered without errors
    TrafficLight *trafficLight;

    // Contains the section on proofs
    QScrollArea *proofsScrollArea;
};