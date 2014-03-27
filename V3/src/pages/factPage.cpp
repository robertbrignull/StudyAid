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
#include "forms/factForm.h"

#include "pages/factPage.h"

FactPage::FactPage(ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    FactForm *factEditForm = new FactForm();
    FormDialog *factEditDialog = new FormDialog(this, factEditForm, QString("Edit the fact..."), QString("Change"));

    DeleteDialog *factDeleteDialog = new DeleteDialog(this, "Are you sure you want to delete this fact?");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    QWidget *crumbWidget = new QWidget();
    crumbWidget->setFixedWidth(700);
    QHBoxLayout *crumbLayout = new QHBoxLayout(crumbWidget);
    crumbLayout->setContentsMargins(0, 0, 0, 0);

    ClickableQLabel *coursesLabel = new ClickableQLabel("Courses");
    ClickableQLabel *factsLabel = new ClickableQLabel("Linear Algebra");
    QLabel *currentFactLabel = new QLabel(" / Vector Space");
    QLabel *sep1Label = new QLabel(" / ");

    QFont font = coursesLabel->font();
    font.setPointSize(14);
    coursesLabel->setFont(font);
    factsLabel->setFont(font);
    currentFactLabel->setFont(font);
    sep1Label->setFont(font);

    QPalette palette = coursesLabel->palette();

    palette.setColor(QPalette::WindowText, Qt::blue);
    palette.setColor(QPalette::Text, Qt::blue);
    coursesLabel->setPalette(palette);
    factsLabel->setPalette(palette);

    palette.setColor(QPalette::WindowText, Qt::gray);
    palette.setColor(QPalette::Text, Qt::gray);
    currentFactLabel->setPalette(palette);
    sep1Label->setPalette(palette);

    crumbLayout->addWidget(coursesLabel);
    crumbLayout->addWidget(sep1Label);
    crumbLayout->addWidget(factsLabel);
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

    QLabel *factLabel = new QLabel("Linear Algebra");
    QFont factFont = factLabel->font();
    factFont.setPointSize(38);
    factLabel->setFont(factFont);

    ImageButton *editFactButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editFactVLayout = new QVBoxLayout();
    editFactVLayout->addSpacing(16);
    editFactVLayout->addWidget(editFactButton);

    ImageButton *deleteFactButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteFactVLayout = new QVBoxLayout();
    deleteFactVLayout->addSpacing(16);
    deleteFactVLayout->addWidget(deleteFactButton);

    topLayout->addWidget(factLabel);
    topLayout->addStretch(1);
    topLayout->addLayout(editFactVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteFactVLayout);

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



    QTextEdit *statementTextEdit = new QTextEdit();
    splitter->addWidget(statementTextEdit);



    ResizableImage *renderedStatement = new ResizableImage("images/latex/test.png");
    QWidget *statementWidget = new QWidget();

    palette = statementWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    statementWidget->setPalette(palette);
    statementWidget->setAutoFillBackground(true);

    QHBoxLayout *statementLayout = new QHBoxLayout(statementWidget);
    // statementLayout->addStretch(1);
    statementLayout->addWidget(renderedStatement);
    // statementLayout->addStretch(1);
    splitter->addWidget(statementWidget);



    connect(coursesLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(0);
    });

    connect(factsLabel, &ClickableQLabel::clicked, [=](){
        pageStack->setCurrentIndex(1);
    });



    connect(editFactButton, &ImageButton::clicked, [=](){
        std::map<QString, QString> data;
        data.insert(std::pair<QString, QString>(QString("type"), QString("Definition")));
        data.insert(std::pair<QString, QString>(QString("name"), QString("Vector space")));
        factEditForm->setData(data);
        factEditDialog->show();
    });

    connect(factEditDialog, &FormDialog::cancelled, [=](){
        factEditDialog->close();
    });

    connect(factEditDialog, &FormDialog::completed, [=](std::map<QString, QString> data){
        std::cout << "Change fact to: " << data[QString("type")].toStdString() << ", " << data[QString("name")].toStdString() << std::endl;
        factEditDialog->close();
    });

    connect(deleteFactButton, &ImageButton::clicked, [=](){
        factDeleteDialog->show();
    });

    connect(factDeleteDialog, &DeleteDialog::accepted, [=](){
        std::cout << "Deleted fact" << std::endl;
        factDeleteDialog->close();
        pageStack->setCurrentIndex(1);
    });

    connect(factDeleteDialog, &DeleteDialog::cancelled, [=](){
        factDeleteDialog->close();
    });
}