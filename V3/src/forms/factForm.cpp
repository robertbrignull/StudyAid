#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

#include "database/methods.h"

#include "forms/factForm.h"

FactForm::FactForm(QWidget *parent)
    : Form(parent)
{
    fact = Fact();



    QHBoxLayout *outerLayout = new QHBoxLayout(this);
    QGridLayout *gridLayout = new QGridLayout();

    outerLayout->addStretch(1);
    outerLayout->addLayout(gridLayout);
    outerLayout->addStretch(1);



    QHBoxLayout *typeLeftLayout = new QHBoxLayout();
    QHBoxLayout *typeRightLayout = new QHBoxLayout();

    typeInput = new QComboBox();

    std::vector<FactType> types = Database::findAllFactTypes();
    for (auto it = types.begin(); it != types.end(); it++) {
        typeInput->addItem(QString::fromStdString(it->fact_type));
    }

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



    connect(nameInput, SIGNAL(textChanged(QString)), this, SLOT(checkValidity()));
    connect(typeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(checkValidity()));
}

void FactForm::clear()
{
    nameInput->setText("");
    typeInput->setCurrentIndex(0);
    currentlyValid = isValid();
}

bool FactForm::isValid()
{
    return (nameInput->text() != "" && typeInput->currentIndex() != -1);
}

void FactForm::setData(Fact fact)
{
    this->fact = fact;

    int i = typeInput->findText(QString::fromStdString(fact.type));
    typeInput->setCurrentIndex((i != -1) ? i : 0);

    nameInput->setText(QString::fromStdString(fact.name));
}

Fact FactForm::getData()
{
    fact.type = typeInput->currentText().toStdString();
    fact.name = nameInput->text().toStdString();

    return fact;
}