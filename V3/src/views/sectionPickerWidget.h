#pragma once

#include <iostream>
#include <map>

#include "database/structures.h"

#include <QWidget>

class Model;
class ResizableStackedWidget;
class QVBoxLayout;
class FactForm;
class SectionForm;
class Dialog;
class ImageButton;
class ClickableQLabel;

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactForm *factAddForm, Dialog *factAddDialog, SectionForm *sectionEditForm, Dialog *sectionEditDialog, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    Fact fact;

    QVBoxLayout *layout;

    ImageButton *deleteSectionButton;
    Dialog *sectionDeleteDialog;

    ImageButton *editSectionButton;
    SectionForm *sectionEditForm;
    Dialog *sectionEditDialog;

    ImageButton *addFactButton;
    FactForm *factAddForm;
    Dialog *factAddDialog;

    // The name of this section
    ClickableQLabel *sectionLabel;

    // A map from ids to SectionPickerWidgets
    std::map<int, std::pair<Fact, SectionPickerWidget*> > idSectionPickerMap;

signals:
    void sectionSelected(int id);

public slots:
    void sectionSelectedSlot(int id);

    void factAddButtonClicked();

    void sectionEditButtonClicked();

    void sectionDeleteDialogAccepted();

    void factAddedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factDeletedSlot(int id);
};