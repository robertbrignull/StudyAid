#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "widgets/horizontalSeperator.h"

#include "forms/formDialog.h"

FormDialog::FormDialog(QWidget *parent, Form *form, QString topText, QString buttonText)
    : QDialog(parent)
{
    setFixedWidth(500);
    setModal(true);



    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(topText));

    layout->addSpacing(15);
    layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    layout->addSpacing(15);

    layout->addWidget(form);

    layout->addSpacing(15);
    layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    layout->addSpacing(15);

    QPushButton *cancelButton = new QPushButton("Cancel");
    QPushButton *completeButton = new QPushButton(buttonText);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(completeButton);

    layout->addLayout(buttonLayout);



    connect(cancelButton, &QPushButton::clicked, [=](){
        emit cancelled();
    });

    connect(completeButton, &QPushButton::clicked, [=](){
        emit completed(form->getData());
    });
}