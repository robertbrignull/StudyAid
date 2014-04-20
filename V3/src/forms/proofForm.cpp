#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "forms/proofForm.h"

ProofForm::ProofForm(QWidget *parent)
    : Form(parent)
{
    proof = Proof();

    QHBoxLayout *layout = new QHBoxLayout(this);

    nameInput = new QLineEdit();

    layout->addStretch(1);
    layout->addWidget(new QLabel("Name: "));
    layout->addWidget(nameInput);
    layout->addStretch(1);
    
    connect(nameInput, SIGNAL(textChanged(QString)), this, SLOT(checkValidity()));
}

void ProofForm::clear()
{
    nameInput->setText("");
    currentlyValid = isValid();
}

bool ProofForm::isValid()
{
    return true;
}

void ProofForm::setData(Proof proof)
{
    this->proof = proof;

    nameInput->setText(QString::fromStdString(proof.name));
}

Proof ProofForm::getData()
{
    proof.name = nameInput->text().toStdString();

    return proof;
}