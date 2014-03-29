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

void ProofForm::setData(std::map<std::string, std::string> data)
{
    nameInput->setText(QString::fromStdString(data.at("name")));
}

std::map<std::string, std::string> ProofForm::getData()
{
    std::map<std::string, std::string> data;

    data.insert(std::pair<std::string, std::string>("name", nameInput->text().toStdString()));

    return data;
}