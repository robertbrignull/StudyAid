#pragma once

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class BreadCrumbs;
class CourseForm;
class FactForm;
class SectionForm;
class Dialog;
class QLabel;
class Splitter;
class QVBoxLayout;
class SectionPickerWidget;
class FactListView;
class ImageButton;
class QScrollArea;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    BreadCrumbs *breadCrumbs;

    ImageButton *editCourseButton;
    CourseForm *courseEditForm;
    Dialog *courseEditDialog;

    ImageButton *deleteCourseButton;
    Dialog *courseDeleteDialog;

    FactForm *factAddForm;
    Dialog *factAddDialog;

    SectionForm *sectionEditForm;
    Dialog *sectionEditDialog;

    // Both labels that hold the name of the current course
    QLabel *courseLabel;

    // THe splitter contains the SectionPicker and FactListView
    Splitter *splitter;

    QScrollArea *pickerScrollArea, *courseScrollArea;
    QVBoxLayout *pickerScrollLayout, *courseScrollLayout;
    SectionPickerWidget *sectionPicker;
    FactListView *factListView;

public slots:
    void courseEditButtonClicked();
    void courseEditDialogCompleted();

    void courseDeleteDialogAccepted();

    void factAddFormCompleted();

    void sectionEditFormCompleted();

    void courseSelectedChangedSlot(Course course);
    void courseEditedSlot(Course course);
};