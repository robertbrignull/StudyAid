#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QScrollArea>
#include <QTextEdit>
#include <QTimer>

#include "model.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/splitter.h"
#include "widgets/resizableImage.h"
#include "widgets/dependenciesWidget.h"
#include "widgets/breadCrumbs.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/proofForm.h"

#include "pages/proofPage.h"

ProofPage::ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    ProofForm *proofEditForm = new ProofForm();
    FormDialog *proofEditDialog = new FormDialog(this, proofEditForm, "Edit the proof...", "Change");

    DeleteDialog *proofDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this proof?");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    //  ##   ## #######   ###   #####   ####### #####
    //  ##   ## ##       ## ##  ##  ##  ##      ##  ##
    //  ##   ## ##      ##   ## ##   ## ##      ##   ##
    //  ####### #####   ##   ## ##   ## #####   ##  ##
    //  ##   ## ##      ####### ##   ## ##      #####
    //  ##   ## ##      ##   ## ##  ##  ##      ##  ##
    //  ##   ## ####### ##   ## #####   ####### ##   ##

    // The breadcrumbs show the current course and provide
    // a way to go back to the courses screen.
    // It is presented like a filepath.

    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    BreadCrumbs *breadCrumbs = new BreadCrumbs(3, model, pageStack);
    breadCrumbs->setFixedWidth(700);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(breadCrumbs);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    // Now show the name of the current proof and some buttons to
    // edit it, delete it or add a new dependency.

    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *factLabel = new QLabel("Vector space proof");
    QFont factFont = factLabel->font();
    factFont.setPointSize(38);
    factLabel->setFont(factFont);

    ImageButton *editProofButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editProofVLayout = new QVBoxLayout();
    editProofVLayout->addSpacing(16);
    editProofVLayout->addWidget(editProofButton);

    ImageButton *deleteProofButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteProofVLayout = new QVBoxLayout();
    deleteProofVLayout->addSpacing(16);
    deleteProofVLayout->addWidget(deleteProofButton);

    topLayout->addWidget(factLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(editProofVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteProofVLayout);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);



    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    outerLayout->addSpacing(20);



    //  ######   #####  #####   ##    ##
    //  ##   ## ##   ## ##  ###  ##  ##
    //  ##   ## ##   ## ##   ##   ####
    //  ######  ##   ## ##   ##    ##
    //  ##   ## ##   ## ##   ##    ##
    //  ##   ## ##   ## ##  ###    ##
    //  ######   #####  #####      ##

    // Use a vertical splitter to divide the areas.

    Splitter *splitter = new Splitter(Qt::Vertical);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    // The first area is a large text editing widget, this is
    // used to edit the proof's body.
    // The QTextEdit does its own scrolling.

    QTextEdit *bodyTextEdit = new QTextEdit();
    QFont font = bodyTextEdit->font();
    font.setPointSize(12);
    bodyTextEdit->setFont(font);
    splitter->addWidget(bodyTextEdit);

    QTimer *bodySaveTimer = new QTimer(this);
    bodySaveTimer->setSingleShot(true);
    bodySaveTimer->setInterval(200);

    connect(bodyTextEdit, SIGNAL(textChanged()), bodySaveTimer, SLOT(start()));
    // connect(bodySaveTimer, SIGNAL(timeout()), this, SLOT(saveBody()));



    // The second area contains the rendered statement.

    QScrollArea *bodyScrollArea = new QScrollArea();
    bodyScrollArea->setWidgetResizable(true);
    bodyScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *bodyWidget = new QWidget();

    QPalette palette = bodyWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    bodyWidget->setPalette(palette);
    bodyWidget->setAutoFillBackground(true);

    ResizableImage *bodyImage = new ResizableImage("images/latex/test.png");

    QHBoxLayout *bodyHLayout = new QHBoxLayout();
    bodyHLayout->addStretch(1);
    bodyHLayout->addWidget(bodyImage);
    bodyHLayout->addStretch(1);

    QVBoxLayout *bodyVLayout = new QVBoxLayout();
    bodyVLayout->addLayout(bodyHLayout);
    bodyVLayout->addStretch(1);

    bodyWidget->setLayout(bodyVLayout);
    bodyScrollArea->setWidget(bodyWidget);
    splitter->addWidget(bodyScrollArea);



    // The third area shows the dependencies for this proof.
    // It shows the names of the facts, clicking one takes you
    // to that fact page.

    QScrollArea *depsScrollArea = new QScrollArea();
    depsScrollArea->setWidgetResizable(true);
    depsScrollArea->setFrameShape(QFrame::NoFrame);

    DependenciesWidget *depsWidget = new DependenciesWidget();
    depsScrollArea->setWidget(depsWidget);
    splitter->addWidget(depsScrollArea);



    //  #####  ####  #####  ##   ##   ###   ##       #####
    // ##   ##  ##  ##   ## ###  ##  ## ##  ##      ##   ##
    //  ##      ##  ##      ###  ## ##   ## ##       ##
    //   ###    ##  ##      ####### ##   ## ##        ###
    //     ##   ##  ##  ### ##  ### ####### ##          ##
    // ##   ##  ##  ##   ## ##  ### ##   ## ##      ##   ##
    //  #####  ####  #####  ##   ## ##   ## #######  #####

    connect(editProofButton, &ImageButton::clicked, [=](){
        std::map<std::string, std::string> data;
        data.insert(std::pair<std::string, std::string>("name", "Vector space proof"));
        proofEditForm->setData(data);
        proofEditDialog->show();
    });

    connect(proofEditDialog, &FormDialog::cancelled, [=](){
        proofEditDialog->close();
    });

    connect(proofEditDialog, &FormDialog::completed, [=](std::map<std::string, std::string> data){
        std::cout << "Change proof to: " << data.at("name") << std::endl;
        proofEditDialog->close();
    });

    connect(deleteProofButton, &ImageButton::clicked, [=](){
        proofDeleteDialog->show();
    });

    connect(proofDeleteDialog, &DeleteDialog::accepted, [=](){
        std::cout << "Deleted proof" << std::endl;
        proofDeleteDialog->close();
        pageStack->setCurrentIndex(2);
    });

    connect(proofDeleteDialog, &DeleteDialog::cancelled, [=](){
        proofDeleteDialog->close();
    });



    connect(depsWidget, &DependenciesWidget::viewButtonClicked, [=](int id){
        std::cout << "Selecting fact: " << id << std::endl;
        pageStack->setCurrentIndex(2);
    });
}



//   #####  ##       #####  ########  #####
//  ##   ## ##      ##   ##    ##    ##   ##
//   ##     ##      ##   ##    ##     ##
//    ###   ##      ##   ##    ##      ###
//      ##  ##      ##   ##    ##        ##
//  ##   ## ##      ##   ##    ##    ##   ##
//   #####  #######  #####     ##     #####