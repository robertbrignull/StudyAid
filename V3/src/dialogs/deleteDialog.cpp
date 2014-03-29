#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "widgets/horizontalSeperator.h"

#include "dialogs/deleteDialog.h"

DeleteDialog::DeleteDialog(QWidget *parent, std::string text)
    : QDialog(parent)
{
    setFixedWidth(500);
    setModal(true);



    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel(QString::fromStdString(text));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    layout->addSpacing(15);
    layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    layout->addSpacing(15);

    QPushButton *cancelButton = new QPushButton("Cancel");
    QPushButton *acceptButton = new QPushButton("Delete");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(acceptButton);

    layout->addLayout(buttonLayout);



    connect(cancelButton, &QPushButton::clicked, [=](){
        emit cancelled();
    });

    connect(acceptButton, &QPushButton::clicked, [=](){
        emit accepted();
    });
}