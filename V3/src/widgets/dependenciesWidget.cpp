#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>

#include "widgets/clickableQLabel.h"
#include "widgets/imageButton.h"
#include "dialogs/deleteDialog.h"

#include "widgets/dependenciesWidget.h"

DependenciesWidget::DependenciesWidget(QWidget *parent)
    : QWidget(parent)
{
    DeleteDialog *depDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this dependency?");

    

    ImageButton *dep1DeleteButton = new ImageButton(QPixmap(":/images/cross_black.png"), QSize(16, 16));
    ClickableQLabel *dep1Label = new ClickableQLabel("Dependent fact 1");

    QPalette dep1Palette = dep1Label->palette();
    dep1Palette.setColor(QPalette::WindowText, Qt::blue);
    dep1Palette.setColor(QPalette::Text, Qt::blue);
    dep1Label->setPalette(dep1Palette);

    QHBoxLayout *dep1Layout = new QHBoxLayout();
    dep1Layout->addWidget(dep1DeleteButton);
    dep1Layout->addWidget(dep1Label);
    dep1Layout->addStretch(1);



    ImageButton *dep2DeleteButton = new ImageButton(QPixmap(":/images/cross_black.png"), QSize(16, 16));
    ClickableQLabel *dep2Label = new ClickableQLabel("Dependent fact 1");

    QPalette dep2Palette = dep2Label->palette();
    dep2Palette.setColor(QPalette::WindowText, Qt::blue);
    dep2Palette.setColor(QPalette::Text, Qt::blue);
    dep2Label->setPalette(dep2Palette);

    QHBoxLayout *dep2Layout = new QHBoxLayout();
    dep2Layout->addWidget(dep2DeleteButton);
    dep2Layout->addWidget(dep2Label);
    dep2Layout->addStretch(1);



    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(dep1Layout);
    layout->addLayout(dep2Layout);
    layout->addStretch(1);



    connect(dep1DeleteButton, &ImageButton::clicked, [=](){
        depBeingDeleted = 0;
        depDeleteDialog->show();
    });

    connect(dep1DeleteButton, &ImageButton::clicked, [=](){
        depBeingDeleted = 1;
        depDeleteDialog->show();
    });



    connect(depDeleteDialog, &DeleteDialog::cancelled, [=](){
        depDeleteDialog->close();
    });

    connect(depDeleteDialog, &DeleteDialog::accepted, [=](){
        depDeleteDialog->close();
        std::cout << "Deleting dependency " << depBeingDeleted << std::endl;
    });



    connect(dep1Label, &ClickableQLabel::clicked, [=](){
        emit viewButtonClicked(0);
    });

    connect(dep2Label, &ClickableQLabel::clicked, [=](){
        emit viewButtonClicked(1);
    });
}