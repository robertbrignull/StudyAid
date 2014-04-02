#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "widgets/horizontalSeperator.h"

#include "dialogs/formDialog.h"

FormDialog::FormDialog(QWidget *parent, Form *form, std::string topText, std::string buttonText)
    : QDialog(parent)
{
    setFixedWidth(500);
    setModal(true);



    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(QString::fromStdString(topText)));

    layout->addSpacing(15);
    layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    layout->addSpacing(15);

    layout->addWidget(form);

    layout->addSpacing(15);
    layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    layout->addSpacing(15);

    cancelButton = new QPushButton("Cancel");
    completeButton = new QPushButton(QString::fromStdString(buttonText));

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