#pragma once

#include <iostream>
#include <map>

#include "database/structures.h"

#include <QWidget>

class Model;
class QPaintEvent;
class QVBoxLayout;
class ClickableQLabel;

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(Fact fact, Model *model, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);



    Model *model;

    Fact fact;

    QVBoxLayout *layout;

    // The name of this section
    ClickableQLabel *sectionLabel;

    // A map from ids to SectionPickerWidgets
    std::map<int, SectionPickerWidget*> idSectionPickerMap;

signals:
    void sectionSelected(int id);

public slots:
    void sectionSelectedSlot(int id);

    void factAddedSlot(Fact fact);
    void factEditedSlot(Fact fact);
    void factOrderingEditedSlot(Fact fact);
    void factDeletedSlot(int id);

private:
    void insertSectionPickerWidget(SectionPickerWidget *sectionPickerWidget);
};