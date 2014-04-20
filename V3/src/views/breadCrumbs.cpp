#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QString>

#include "model.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/clickableQLabel.h"

#include "views/breadCrumbs.h"

BreadCrumbs::BreadCrumbs(int level, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;
    this->level = level;



    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    rootText = "Courses";
    coursesLabel = new ClickableQLabel(rootText);

    QFont font = coursesLabel->font();
    font.setPointSize(14);

    QPalette bluePalette = coursesLabel->palette();
    bluePalette.setColor(QPalette::WindowText, Qt::blue);
    bluePalette.setColor(QPalette::Text, Qt::blue);

    QPalette greyPalette = coursesLabel->palette();
    greyPalette.setColor(QPalette::WindowText, Qt::gray);
    greyPalette.setColor(QPalette::Text, Qt::gray);

    coursesLabel->setFont(font);
    coursesLabel->setPalette(bluePalette);
    layout->addWidget(coursesLabel);

    fontMetrics = new QFontMetrics(font);

    connect(coursesLabel, SIGNAL(clicked()), this, SLOT(coursesLabelClicked()));

    if (level == 1) {
        currentCourseLabel = new QLabel("");
        currentCourseLabel->setFont(font);
        currentCourseLabel->setPalette(greyPalette);

        layout->addWidget(newSeperator());
        layout->addWidget(currentCourseLabel);

        connect(model, SIGNAL(courseSelectedChanged(Course)), this, SLOT(courseSelectedChangedSlot(Course)));
        connect(model, SIGNAL(courseEdited(Course)), this, SLOT(courseEditedSlot(Course)));
    }
    else if (level > 1) {
        factsLabel = new ClickableQLabel("");
        factsLabel->setFont(font);
        factsLabel->setPalette(bluePalette);

        layout->addWidget(newSeperator());
        layout->addWidget(factsLabel);

        connect(model, SIGNAL(courseSelectedChanged(Course)), this, SLOT(courseSelectedChangedSlot(Course)));
        connect(model, SIGNAL(courseEdited(Course)), this, SLOT(courseEditedSlot(Course)));
        connect(factsLabel, SIGNAL(clicked()), this, SLOT(factsLabelClicked()));

        if (level == 2) {
            currentFactLabel = new QLabel("");
            currentFactLabel->setFont(font);
            currentFactLabel->setPalette(greyPalette);

            layout->addWidget(newSeperator());
            layout->addWidget(currentFactLabel);

            connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
            connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
        }
        else if (level > 2) {
            proofsLabel = new ClickableQLabel("");
            proofsLabel->setFont(font);
            proofsLabel->setPalette(bluePalette);
            
            layout->addWidget(newSeperator());
            layout->addWidget(proofsLabel);

            connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
            connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
            connect(proofsLabel, SIGNAL(clicked()), this, SLOT(proofsLabelClicked()));

            currentProofLabel = new QLabel("");
            currentProofLabel->setFont(font);
            currentProofLabel->setPalette(greyPalette);

            layout->addWidget(newSeperator());
            layout->addWidget(currentProofLabel);

            connect(model, SIGNAL(proofSelectedChanged(Proof)), this, SLOT(proofSelectedChangedSlot(Proof)));
            connect(model, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
        }
    }

    layout->addStretch(1);
}

BreadCrumbs::~BreadCrumbs()
{
    delete fontMetrics;
}

void BreadCrumbs::courseSelectedChangedSlot(Course course)
{
    courseName = QString::fromStdString(course.name);

    adjustLabels();
}

void BreadCrumbs::factSelectedChangedSlot(Fact fact)
{
    factName = QString::fromStdString(fact.name);

    adjustLabels();
}

void BreadCrumbs::proofSelectedChangedSlot(Proof proof)
{
    proofName = (proof.name != "") ? QString::fromStdString(proof.name) : "Proof";

    adjustLabels();
}

void BreadCrumbs::courseEditedSlot(Course course)
{
    if (course.id == model->getCourseSelected().id) {
        courseSelectedChangedSlot(course);
    }
}

void BreadCrumbs::factEditedSlot(Fact fact)
{
    if (fact.id == model->getFactSelected().id) {
        factSelectedChangedSlot(fact);
    }
}

void BreadCrumbs::proofEditedSlot(Proof proof)
{
    if (proof.id == model->getProofSelected().id) {
        proofSelectedChangedSlot(proof);
    }
}

void BreadCrumbs::coursesLabelClicked()
{
    pageStack->setCurrentIndex(0);
}

void BreadCrumbs::factsLabelClicked()
{
    pageStack->setCurrentIndex(1);
}

void BreadCrumbs::proofsLabelClicked()
{
    pageStack->setCurrentIndex(2);
}

QLabel *BreadCrumbs::newSeperator()
{
    QLabel *sep = new QLabel(" / ");

    QFont font = sep->font();
    font.setPointSize(14);
    sep->setFont(font);

    QPalette greyPalette = sep->palette();
    greyPalette.setColor(QPalette::WindowText, Qt::gray);
    greyPalette.setColor(QPalette::Text, Qt::gray);
    sep->setPalette(greyPalette);

    return sep;
}

void BreadCrumbs::adjustLabels()
{
    if (level == 1) {
        coursesLabel->setText(rootText);
        currentCourseLabel->setText(courseName);

        coursesLabel->setText(fontMetrics->elidedText(coursesLabel->text(), Qt::ElideRight, coursesLabel->width()));
        currentCourseLabel->setText(fontMetrics->elidedText(currentCourseLabel->text(), Qt::ElideRight, currentCourseLabel->width()));
    }
    else if (level == 2) {
        coursesLabel->setText(rootText);
        factsLabel->setText(courseName);
        currentFactLabel->setText(factName);

        coursesLabel->setText(fontMetrics->elidedText(coursesLabel->text(), Qt::ElideRight, coursesLabel->width()));
        factsLabel->setText(fontMetrics->elidedText(factsLabel->text(), Qt::ElideRight, factsLabel->width()));
        currentFactLabel->setText(fontMetrics->elidedText(currentFactLabel->text(), Qt::ElideRight, currentFactLabel->width()));
    }
    else if (level == 3) {
        coursesLabel->setText(rootText);
        factsLabel->setText(courseName);
        proofsLabel->setText(factName);
        currentProofLabel->setText(proofName);

        coursesLabel->setText(fontMetrics->elidedText(coursesLabel->text(), Qt::ElideRight, coursesLabel->width()));
        factsLabel->setText(fontMetrics->elidedText(factsLabel->text(), Qt::ElideRight, factsLabel->width()));
        proofsLabel->setText(fontMetrics->elidedText(proofsLabel->text(), Qt::ElideRight, proofsLabel->width()));
        currentProofLabel->setText(fontMetrics->elidedText(currentProofLabel->text(), Qt::ElideRight, currentProofLabel->width()));
    }
}