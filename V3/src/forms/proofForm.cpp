#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "forms/proofForm.h"

ProofForm::ProofForm(QWidget *parent)
    : Form(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    nameInput = new QLineEdit();

    layout->addStretch(1);
    layout->addWidget(new QLabel("Name: "));
    layout->addWidget(nameInput);
    layout->addStretch(1);
}

void ProofForm::setData(std::map<QString, QString> data)
{
    nameInput->setText(data[QString("name")]);
}

std::map<QString, QString> ProofForm::getData()
{
    std::map<QString, QString> data;

    data.insert(std::pair<QString, QString>(QString("name"), nameInput->text()));

    return data;
}