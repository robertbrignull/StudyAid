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
class ImageButton;

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
    FormDialog *courseEditDialog;

    ImageButton *deleteCourseButton;
    DeleteDialog *courseDeleteDialog;

    // Both labels that hold the name of the current course
    QLabel *courseLabel;

    // THe splitter contains the SectionPicker and FactListView
    Splitter *splitter;

    QVBoxLayout *pickerScrollLayout, *courseScrollLayout;
    SectionPickerWidget *sectionPicker;
    FactListView *factListView;

public slots:
    void courseEditButtonClicked();
    void courseEditDialogCompleted(std::map<std::string, std::string> data);

    void courseDeleteDialogAccepted();

    void courseSelectedChangedSlot(Course course);
    void courseEditedSlot(Course course);
};