#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>

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

    QDialogButtonBox *dialogButtonBox = new QDialogButtonBox();
    dialogButtonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);
    dialogButtonBox->addButton(confirmButton, QDialogButtonBox::AcceptRole);

    layout->addWidget(dialogButtonBox);



    connect(dialogButtonBox, SIGNAL(accepted()), this, SIGNAL(accepted()));
    connect(dialogButtonBox, SIGNAL(rejected()), this, SIGNAL(rejected()));
}