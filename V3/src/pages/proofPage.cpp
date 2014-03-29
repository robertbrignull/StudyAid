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
#include "widgets/dependenciesWidget.h"
#include "dialogs/deleteDialog.h"
#include "dialogs/formDialog.h"
#include "forms/proofForm.h"

#include "pages/proofPage.h"

ProofPage::ProofPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    ProofForm *proofEditForm = new ProofForm();
    FormDialog *proofEditDialog = new FormDialog(this, proofEditForm, "Edit the proof...", "Change");

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



    Splitter *splitter = new Splitter(Qt::Vertical);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    QTextEdit *bodyTextEdit = new QTextEdit();
    font = bodyTextEdit->font();
    font.setPointSize(12);
    bodyTextEdit->setFont(font);
    bodyTextEdit->setText("Let $X,Y,Z$ be sets with strict total orders\n\\begin{enumerate}\n\\item If $f:X\\to Y$ is an order-isomorphism, then so is its inverse\n\\item If $f:X\\to Y$, $g:Y\\to Z$ are order-isomorphisms, then so if $g\\circ f:X\\to Z$\n\\item If $X$ is well-ordered, then any subset $Z\\subseteq X$ is well-ordered by restriction\n\\end{enumerate}");
    splitter->addWidget(bodyTextEdit);



    QScrollArea *bodyScrollArea = new QScrollArea();
    bodyScrollArea->setWidgetResizable(true);
    bodyScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *bodyWidget = new QWidget();

    palette = bodyWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    bodyWidget->setPalette(palette);
    bodyWidget->setAutoFillBackground(true);

    QHBoxLayout *bodyHLayout = new QHBoxLayout();
    bodyHLayout->addStretch(1);
    bodyHLayout->addWidget(new ResizableImage("images/latex/test.png"));
    bodyHLayout->addStretch(1);

    QVBoxLayout *bodyVLayout = new QVBoxLayout();
    bodyVLayout->addLayout(bodyHLayout);
    bodyVLayout->addStretch(1);

    bodyWidget->setLayout(bodyVLayout);
    bodyScrollArea->setWidget(bodyWidget);
    splitter->addWidget(bodyScrollArea);



    QScrollArea *depsScrollArea = new QScrollArea();
    depsScrollArea->setWidgetResizable(true);
    depsScrollArea->setFrameShape(QFrame::NoFrame);

    DependenciesWidget *depsWidget = new DependenciesWidget();
    depsScrollArea->setWidget(depsWidget);
    splitter->addWidget(depsScrollArea);

    

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