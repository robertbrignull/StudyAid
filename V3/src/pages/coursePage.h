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
class QPushButton;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);



    Model *model;
    ResizableStackedWidget *pageStack;

    QPushButton *newWindowButton;

    BreadCrumbs *breadCrumbs;

    ImageButton *editCourseButton;
    CourseForm *courseEditForm;
    Dialog *courseEditDialog;

    ImageButton *deleteCourseButton;
    Dialog *courseDeleteDialog;

    // Both labels that hold the name of the current course
    QLabel *courseLabel;

    // THe splitter contains the SectionPicker and FactListView
    Splitter *splitter;

    QScrollArea *pickerScrollArea, *courseScrollArea;
    QVBoxLayout *pickerScrollLayout, *courseScrollLayout;
    SectionPickerWidget *sectionPicker;
    FactListView *factListView;

signals:
    void requestNewWindow(int pageIndex, Course course, Fact fact, Proof proof);

public slots:
    void courseEditButtonClicked();
    void courseEditDialogCompleted();

    void courseDeleteDialogAccepted();

    void sectionSelected(int id);

    void newWindowButtonClicked();

    void courseSelectedChangedSlot(Course course);
    void courseEditedSlot(Course course);
    void courseDeletedSlot(int id);
};