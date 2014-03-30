#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

#include "forms/factForm.h"

FactForm::FactForm(QWidget *parent)
    : Form(parent)
{
    QHBoxLayout *outerLayout = new QHBoxLayout(this);
    QGridLayout *gridLayout = new QGridLayout();

    outerLayout->addStretch(1);
    outerLayout->addLayout(gridLayout);
    outerLayout->addStretch(1);



    QHBoxLayout *typeLeftLayout = new QHBoxLayout();
    QHBoxLayout *typeRightLayout = new QHBoxLayout();

    typeInput = new QComboBox();
    typeInput->addItem("Section");
    typeInput->addItem("Axiom");
    typeInput->addItem("Definition");
    typeInput->addItem("Proposition");
    typeInput->addItem("Lemma");
    typeInput->addItem("Theorem");
    typeInput->addItem("Corollary");
    typeInput->addItem("Example");
    typeInput->addItem("Remark");

    typeLeftLayout->addStretch(1);
    typeLeftLayout->addWidget(new QLabel("Type: "));
    typeRightLayout->addWidget(typeInput);
    typeRightLayout->addStretch(1);

    gridLayout->addLayout(typeLeftLayout, 0, 0);
    gridLayout->addLayout(typeRightLayout, 0, 1);



    QHBoxLayout *nameLeftLayout = new QHBoxLayout();
    QHBoxLayout *nameRightLayout = new QHBoxLayout();

    nameInput = new QLineEdit();

    nameLeftLayout->addStretch(1);
    nameLeftLayout->addWidget(new QLabel("Name: "));
    nameRightLayout->addWidget(nameInput);
    nameRightLayout->addStretch(1);

    gridLayout->addLayout(nameLeftLayout, 1, 0);
    gridLayout->addLayout(nameRightLayout, 1, 1);
}

void FactForm::setData(std::map<std::string, std::string> data)
{
    int i = typeInput->findText(QString::fromStdString(data.at("type")));
    typeInput->setCurrentIndex((i != -1) ? i : 0);

    nameInput->setText(QString::fromStdString(data.at("name")));
}

std::map<std::string, std::string> FactForm::getData()
{
    std::map<std::string, std::string> data;

    data.insert(std::pair<std::string, std::string>("type", typeInput->currentText().toStdString()));
    data.insert(std::pair<std::string, std::string>("name", nameInput->text().toStdString()));

    return data;
}