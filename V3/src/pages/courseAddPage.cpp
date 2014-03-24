#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

#include "widgets/horizontalSeperator.h"

#include "pages/courseAddPage.h"

CourseAddPage::CourseAddPage(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(500);

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    vLayout->addWidget(new QLabel("Add a new course..."));

    vLayout->addSpacing(15);
    vLayout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    vLayout->addSpacing(15);

    QLineEdit *nameInput = new QLineEdit();
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addStretch(1);
    nameLayout->addWidget(new QLabel("Name: "));
    nameLayout->addWidget(nameInput);
    nameLayout->addStretch(1);

    vLayout->addLayout(nameLayout);

    vLayout->addSpacing(15);
    vLayout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    vLayout->addSpacing(15);

    QPushButton *cancelButton = new QPushButton("Cancel");
    QPushButton *createButton = new QPushButton("Create");

    QHBoxLayout *createLayout = new QHBoxLayout();
    createLayout->addWidget(cancelButton);
    createLayout->addStretch(1);
    createLayout->addWidget(createButton);
    vLayout->addLayout(createLayout);

    connect(createButton, &QPushButton::clicked, [=](){
        emit courseAdded(0);
    });

    connect(cancelButton, &QPushButton::clicked, [=](){
        emit cancelled();
    });
}