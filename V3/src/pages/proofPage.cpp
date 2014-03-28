#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QScrollArea>
#include <QTextEdit>

#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/horizontalSeperator.h"
#include "widgets/clickableQLabel.h"
#include "widgets/splitter.h"
#include "widgets/resizableImage.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/proofForm.h"

#include "pages/proofPage.h"

ProofPage::ProofPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    ProofForm *proofEditForm = new ProofForm();
    FormDialog *proofEditDialog = new FormDialog(this, proofEditForm, QString("Edit the proof..."), QString("Change"));

    DeleteDialog *proofDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this proof?");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    QWidget *crumbWidget = new QWidget();
    crumbWidget->setFixedWidth(700);
    QHBoxLayout *crumbLayout = new QHBoxLayout(crumbWidget);
    crumbLayout->setContentsMargins(0, 0, 0, 0);

    ClickableQLabel *coursesLabel = new ClickableQLabel("Courses");
    ClickableQLabel *factsLabel = new ClickableQLabel("Linear Algebra");
    ClickableQLabel *proofsLabel = new ClickableQLabel("Vector space");
    QLabel *currentFactLabel = new QLabel(" / Proof");
    QLabel *sep1Label = new QLabel(" / ");
    QLabel *sep2Label = new QLabel(" / ");

    QFont font = coursesLabel->font();
    font.setPointSize(14);
    coursesLabel->setFont(font);
    factsLabel->setFont(font);
    proofsLabel->setFont(font);
    currentFactLabel->setFont(font);
    sep1Label->setFont(font);
    sep2Label->setFont(font);

    QPalette palette = coursesLabel->palette();

    palette.setColor(QPalette::WindowText, Qt::blue);
    palette.setColor(QPalette::Text, Qt::blue);
    coursesLabel->setPalette(palette);
    factsLabel->setPalette(palette);
    proofsLabel->setPalette(palette);

    palette.setColor(QPalette::WindowText, Qt::gray);
    palette.setColor(QPalette::Text, Qt::gray);
    currentFactLabel->setPalette(palette);
    sep1Label->setPalette(palette);
    sep2Label->setPalette(palette);

    crumbLayout->addWidget(coursesLabel);
    crumbLayout->addWidget(sep1Label);
    crumbLayout->addWidget(factsLabel);
    crumbLayout->addWidget(sep2Label);
    crumbLayout->addWidget(proofsLabel);
    crumbLayout->addWidget(currentFactLabel);
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



    outerLayout->addStretch(1);

    

    connect(coursesLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(0);
    });

    connect(factsLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(1);
    });

    connect(proofsLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(2);
    });



    connect(editProofButton, &ImageButton::clicked, [=](){
        std::map<QString, QString> data;
        data.insert(std::pair<QString, QString>(QString("name"), QString("Vector space proof")));
        proofEditForm->setData(data);
        proofEditDialog->show();
    });

    connect(proofEditDialog, &FormDialog::cancelled, [=](){
        proofEditDialog->close();
    });

    connect(proofEditDialog, &FormDialog::completed, [=](std::map<QString, QString> data){
        std::cout << "Change proof to: " << data[QString("name")].toStdString() << std::endl;
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
}