#pragma once

#include "database/structures.h"

#include <QWidget>

class ResizableStackedWidget;
class Model;
class BreadCrumbs;
class CourseForm;
class FormDialog;
class DeleteDialog;
class QLabel;
class Splitter;
class QVBoxLayout;
class SectionPickerWidget;
class FactListView;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    // The BreadCrumbs widgets at the top of page
    BreadCrumbs *breadCrumbs;

    // The form and dialog for editing a course
    CourseForm *courseEditForm;
    FormDialog *courseEditDialog;

    // Dialog for deleting a course
    DeleteDialog *courseDeleteDialog;

    // Both labels that hold the name of the current course
    QLabel *courseLabel;

    // THe splitter contains the SectionPicker and FactListView
    Splitter *splitter;

    // The layouts for the two sides of the splitter
    QVBoxLayout *pickerScrollLayout, *courseScrollLayout;

    // The current section picker
    SectionPickerWidget *sectionPicker;

    // The current fact list view
    FactListView *factListView;

public slots:
    void courseEditButtonClicked();
    void courseEditDialogCompleted(std::map<std::string, std::string> data);

    void courseDeleteDialogAccepted();

    void courseSelectedChangedSlot(Course course);
    void courseEditedSlot(Course course);
};