#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "forms/sectionForm.h"

SectionForm::SectionForm(QWidget *parent)
    : QWidget(parent)
{
    section = Fact();

    QHBoxLayout *layout = new QHBoxLayout(this);

    nameInput = new QLineEdit();

    layout->addStretch(1);
    layout->addWidget(new QLabel("Name: "));
    layout->addWidget(nameInput);
    layout->addStretch(1);
}

void SectionForm::setData(Fact section)
{
    this->section = section;

    nameInput->setText(QString::fromStdString(section.name));
}

Fact SectionForm::getData()
{
    section.name = nameInput->text().toStdString();

    return section;
}