#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QScrollArea>

#include "model.h"
#include "database/methods.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/courseWidget.h"
#include "widgets/sectionPickerWidget.h"
#include "widgets/splitter.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/courseForm.h"
#include "forms/factForm.h"

#include "pages/coursePage.h"

CoursePage::CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    CourseForm *courseEditForm = new CourseForm();
    FormDialog *courseEditDialog = new FormDialog(this, courseEditForm, "Edit the course...", "Change");

    DeleteDialog *courseDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this course?");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    QWidget *crumbWidget = new QWidget();
    crumbWidget->setFixedWidth(700);
    QHBoxLayout *crumbLayout = new QHBoxLayout(crumbWidget);
    crumbLayout->setContentsMargins(0, 0, 0, 0);

    ClickableQLabel *coursesLabel = new ClickableQLabel("Courses");
    QLabel *sepLabel = new QLabel(" / ");
    currentCourseLabel = new QLabel();

    QFont font = coursesLabel->font();
    font.setPointSize(14);
    coursesLabel->setFont(font);
    currentCourseLabel->setFont(font);

    QPalette palette = coursesLabel->palette();

    palette.setColor(QPalette::WindowText, Qt::blue);
    palette.setColor(QPalette::Text, Qt::blue);
    coursesLabel->setPalette(palette);

    palette.setColor(QPalette::WindowText, Qt::gray);
    palette.setColor(QPalette::Text, Qt::gray);
    sepLabel->setPalette(palette);
    currentCourseLabel->setPalette(palette);

    crumbLayout->addWidget(coursesLabel);
    crumbLayout->addWidget(sepLabel);
    crumbLayout->addWidget(currentCourseLabel);
    crumbLayout->addStretch(1);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(crumbWidget);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    courseLabel = new QLabel();
    QFont courseFont = courseLabel->font();
    courseFont.setPointSize(38);
    courseLabel->setFont(courseFont);

    ImageButton *editCourseButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editCourseVLayout = new QVBoxLayout();
    editCourseVLayout->addSpacing(16);
    editCourseVLayout->addWidget(editCourseButton);

    ImageButton *deleteCourseButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteCourseVLayout = new QVBoxLayout();
    deleteCourseVLayout->addSpacing(16);
    deleteCourseVLayout->addWidget(deleteCourseButton);

    topLayout->addWidget(courseLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(editCourseVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteCourseVLayout);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);


    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    outerLayout->addSpacing(20);



    Splitter *splitter = new Splitter(Qt::Horizontal);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    QScrollArea *pickerScrollArea = new QScrollArea();
    pickerScrollArea->setWidgetResizable(true);
    pickerScrollArea->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(pickerScrollArea);

    QWidget *pickerScrollWidget = new QWidget();
    pickerScrollLayout = new QVBoxLayout(pickerScrollWidget);
    pickerScrollArea->setWidget(pickerScrollWidget);

    pickerScrollLayout->addStretch(1);



    QScrollArea *courseScrollArea = new QScrollArea();
    courseScrollArea->setWidgetResizable(true);
    courseScrollArea->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(courseScrollArea);

    QWidget *courseScrollWidget = new QWidget();
    courseScrollLayout = new QVBoxLayout(courseScrollWidget);
    courseScrollArea->setWidget(courseScrollWidget);



    splitter->setSizes(QList<int>({0, 1}));



    connect(coursesLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(0);
    });



    connect(editCourseButton, &ImageButton::clicked, [=](){
        std::map<std::string, std::string> data;
        data.insert(std::pair<std::string, std::string>("name", model->getCourseSelected().name));
        courseEditForm->setData(data);

        courseEditDialog->show();
    });

    connect(courseEditDialog, &FormDialog::cancelled, [=](){
        courseEditDialog->close();
    });

    connect(courseEditDialog, &FormDialog::completed, [=](std::map<std::string, std::string> data){
        Course course = model->getCourseSelected();
        course.name = data.at("name");
        editCourse(course);

        model->editCourse(course);

        courseEditDialog->close();
    });

    connect(deleteCourseButton, &ImageButton::clicked, [=](){
        courseDeleteDialog->show();
    });

    connect(courseDeleteDialog, &DeleteDialog::accepted, [=](){
        deleteCourse(model->getCourseSelected().id);

        model->deleteCourse(model->getCourseSelected().id);

        courseDeleteDialog->close();
        pageStack->setCurrentIndex(0);
    });

    connect(courseDeleteDialog, &DeleteDialog::cancelled, [=](){
        courseDeleteDialog->close();
    });



    connect(model, &Model::courseSelectedChanged, [=](Course course){
        rebuildCourseDetails(course);
        rebuildSectionPicker(course);
        rebuildFactList(course.root_fact);
    });

    connect(model, &Model::courseEdited, [=](Course course){
        if (model->isCourseSelected() && model->getCourseSelected().id == course.id) {
            rebuildCourseDetails(course);
        }
    });

    connect(model, &Model::factAdded, [=](Fact fact){
        if (fact.type == "Section") {
            rebuildSectionPicker(model->getCourseSelected());
        }
        rebuildFactList(model->getCourseSelected().root_fact);
    });

    connect(model, &Model::factEdited, [=](Fact fact){
        if (fact.type == "Section") {
            rebuildSectionPicker(model->getCourseSelected());
        }
        rebuildFactList(model->getCourseSelected().root_fact);
    });

    connect(model, &Model::factDeleted, [=](int){
        rebuildSectionPicker(model->getCourseSelected());
        rebuildFactList(model->getCourseSelected().root_fact);
    });
}

void CoursePage::rebuildSectionPicker(Course course)
{
    while (pickerScrollLayout->count() > 0) {
        delete pickerScrollLayout->takeAt(0)->widget();
    }
    SectionPickerWidget *sectionPicker = new SectionPickerWidget(course.root_fact, course.name);
    pickerScrollLayout->addWidget(sectionPicker);
    pickerScrollLayout->addStretch(1);

    connect(sectionPicker, &SectionPickerWidget::sectionSelected, [=](int id){
        rebuildFactList(id);
    });

    connect(sectionPicker, &SectionPickerWidget::factAdded, [=](Fact fact){
        model->addFact(fact);
        
        if (fact.type != "Section") {
            model->setFactSelected(fact);
            pageStack->setCurrentIndex(2);
        }
    });
}

void CoursePage::rebuildFactList(int id)
{
    while (courseScrollLayout->count() > 0) {
        delete courseScrollLayout->takeAt(0)->widget();
    }
    CourseWidget *courseWidget = new CourseWidget(id);
    courseScrollLayout->addWidget(courseWidget);
    courseScrollLayout->addStretch(1);

    connect(courseWidget, &CourseWidget::viewButtonClicked, [=](int id){
        model->setFactSelected(findFact(id));
        pageStack->setCurrentIndex(2);
    });
}

void CoursePage::rebuildCourseDetails(Course course)
{
    currentCourseLabel->setText(QString::fromStdString(course.name));

    courseLabel->setText(QString::fromStdString(course.name));
}