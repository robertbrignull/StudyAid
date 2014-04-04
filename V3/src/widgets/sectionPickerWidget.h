#pragma once

#include <iostream>
#include <map>

#include "database/structures.h"

#include <QWidget>

class Model;
class ResizableStackedWidget;
class QVBoxLayout;
class FactForm;
class FormDialog;
class ImageButton;
class ClickableQLabel;

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    Fact fact;

    QVBoxLayout *layout;

    FactForm *factAddForm;
    FormDialog *factAddDialog;
    ImageButton *addFactButton;

    // The name of this section
    ClickableQLabel *sectionLabel;

    // A map from ids to SectionPickerWidgets
    std::map<int, std::pair<Fact, SectionPickerWidget*> > idSectionPickerMap;

signals:
    void sectionSelected(int id);

public slots:
    void sectionSelectedSlot(int id);

    void factAddFormCompleted(std::map<std::string, std::string> data);

    void factAddedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factDeletedSlot(int id);
};