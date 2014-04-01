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

class FactPage : public QWidget
{
    Q_OBJECT

public:
    FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

public slots:
    void factEditButtonClicked();
    void factEditDialogCompleted(std::map<std::string, std::string> data);

    void factDeleteDialogAccepted();

    void proofAddDialogCompleted(std::map<std::string, std::string> data);

    void courseSelectedChangedSlot(Course course);
    void courseEditedSlot(Course course);

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

    // Contains the name of the current course
    ClickableQLabel *factsLabel;

    // Contains the name of the current fact
    QLabel *currentFactLabel, *factLabel;

    // Contains the current fact's statement
    QTextEdit *statementTextEdit;

    // Contains the section on proofs
    QScrollArea *proofsScrollArea;
};