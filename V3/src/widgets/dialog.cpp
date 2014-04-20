#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QShowEvent>

#include "widgets/horizontalSeperator.h"
#include "forms/form.h"

#include "widgets/dialog.h"

Dialog::Dialog(QWidget *parent, Form *form, std::string topText, std::string confirmButtonText, std::string cancelButtonText)
    : QDialog(parent)
{
    this->form = form;



    setFixedWidth(500);
    setModal(true);



    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(QString::fromStdString(topText)));

    if (form != nullptr) {
        layout->addSpacing(15);
        layout->addWidget(new HorizontalSeperator(QColor(200, 200, 200), 1));
        layout->addSpacing(15);

        layout->addWidget(form);
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

    if (form != nullptr) {
        connect(form, SIGNAL(valid()), this, SLOT(formValid()));
        connect(form, SIGNAL(invalid()), this, SLOT(formInvalid()));
    }
}

void Dialog::showEvent(QShowEvent *)
{
    if (form != nullptr) {
        form->clear();

        (form->isValid()) ? formValid() : formInvalid();
    }
}

void Dialog::formValid()
{
    confirmButton->setEnabled(true);
}

void Dialog::formInvalid()
{
    confirmButton->setEnabled(false);
}