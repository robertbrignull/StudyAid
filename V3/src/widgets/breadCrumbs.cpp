#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QString>

#include "model.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/clickableQLabel.h"

#include "widgets/breadCrumbs.h"

BreadCrumbs::BreadCrumbs(int level, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;
    this->level = level;



    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    coursesLabel = new ClickableQLabel("Courses");

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

    connect(coursesLabel, SIGNAL(clicked()), this, SLOT(coursesLabelClicked()));

    if (level == 1) {
        currentCourseLabel = new QLabel("");
        currentCourseLabel->setFont(font);
        currentCourseLabel->setPalette(greyPalette);

        layout->addWidget(newSeperator());
        layout->addWidget(currentCourseLabel);

        connect(model, SIGNAL(courseSelectedChanged(Course)), this, SLOT(courseSelectedChangedSlot(Course)));
    }
    else if (level > 1) {
        factsLabel = new ClickableQLabel("");
        factsLabel->setFont(font);
        factsLabel->setPalette(bluePalette);

        layout->addWidget(newSeperator());
        layout->addWidget(factsLabel);

        connect(model, SIGNAL(courseSelectedChanged(Course)), this, SLOT(courseSelectedChangedSlot(Course)));
        connect(factsLabel, SIGNAL(clicked()), this, SLOT(factsLabelClicked()));

        if (level == 2) {
            currentFactLabel = new QLabel("");
            currentFactLabel->setFont(font);
            currentFactLabel->setPalette(greyPalette);

            layout->addWidget(newSeperator());
            layout->addWidget(currentFactLabel);

            connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
        }
        else if (level > 2) {
            proofsLabel = new ClickableQLabel("");
            proofsLabel->setFont(font);
            proofsLabel->setPalette(bluePalette);
            
            layout->addWidget(newSeperator());
            layout->addWidget(proofsLabel);

            connect(model, SIGNAL(factSelectedChanged(Fact)), this, SLOT(factSelectedChangedSlot(Fact)));
            connect(proofsLabel, SIGNAL(clicked()), this, SLOT(proofsLabelClicked()));

            currentProofLabel = new QLabel("");
            currentProofLabel->setFont(font);
            currentProofLabel->setPalette(greyPalette);

            layout->addWidget(newSeperator());
            layout->addWidget(currentProofLabel);

            connect(model, SIGNAL(proofSelectedChanged(Proof)), this, SLOT(proofSelectedChangedSlot(Proof)));
        }
    }

    layout->addStretch(1);
}

void BreadCrumbs::courseSelectedChangedSlot(Course course)
{
    if (level == 1) {
        currentCourseLabel->setText(QString::fromStdString(course.name));
    }
    else if (level > 1) {
        factsLabel->setText(QString::fromStdString(course.name));
    }
}

void BreadCrumbs::factSelectedChangedSlot(Fact fact)
{
    if (level == 2) {
        currentFactLabel->setText(QString::fromStdString(fact.name));
    }
    else if (level > 2) {
        proofsLabel->setText(QString::fromStdString(fact.name));
    }
}

void BreadCrumbs::proofSelectedChangedSlot(Proof proof)
{
    if (level == 3) {
        currentProofLabel->setText(QString::fromStdString(proof.name));
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