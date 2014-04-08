#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "widgets/horizontalSeperator.h"

#include "widgets/dialog.h"

Dialog::Dialog(QWidget *parent, QWidget *body, std::string topText, std::string confirmButtonText, std::string cancelButtonText)
    : QDialog(parent)
{
    setFixedWidth(500);
    setModal(true);



    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(QString::fromStdString(topText)));

    if (body != nullptr) {
        layout->addSpacing(15);
        layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
        layout->addSpacing(15);

        layout->addWidget(body);
    }

    layout->addSpacing(15);
    layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
    layout->addSpacing(15);

    cancelButton = new QPushButton(QString::fromStdString(cancelButtonText));
    confirmButton = new QPushButton(QString::fromStdString(confirmButtonText));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(confirmButton);

    layout->addLayout(buttonLayout);



    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelled()));
    connect(confirmButton, SIGNAL(clicked()), this, SIGNAL(completed()));
}