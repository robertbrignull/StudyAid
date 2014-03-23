#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

#include "pages/courseAddPage.h"

CourseAddPage::CourseAddPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);

    QLineEdit *nameInput = new QLineEdit();

    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Name: "));
    nameLayout->addWidget(nameInput);
    vLayout->addLayout(nameLayout);

    QPushButton *createButton = new QPushButton("Create");
    QPushButton *cancelButton = new QPushButton("Cancel");

    QHBoxLayout *createLayout = new QHBoxLayout();
    createLayout->addStretch(1);
    createLayout->addWidget(createButton);
    createLayout->addSpacing(10);
    createLayout->addWidget(cancelButton);
    createLayout->addStretch(1);
    vLayout->addLayout(createLayout);

    connect(createButton, &QPushButton::clicked, [=](){
        emit courseAdded(0);
    });

    connect(cancelButton, &QPushButton::clicked, [=](){
        emit cancelled();
    });
}