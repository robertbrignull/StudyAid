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
    typeInput->addItem(QString("Axiom"));
    typeInput->addItem(QString("Definition"));
    typeInput->addItem(QString("Proposition"));
    typeInput->addItem(QString("Lemma"));
    typeInput->addItem(QString("Theorem"));
    typeInput->addItem(QString("Corollary"));
    typeInput->addItem(QString("Example"));
    typeInput->addItem(QString("Remark"));

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

void FactForm::setData(std::map<QString, QString> data)
{
    int i = typeInput->findText(data[QString("type")]);
    typeInput->setCurrentIndex((i != -1) ? i : 0);

    nameInput->setText(data[QString("name")]);
}

std::map<QString, QString> FactForm::getData()
{
    std::map<QString, QString> data;

    data.insert(std::pair<QString, QString>(QString("type"), typeInput->currentText()));
    data.insert(std::pair<QString, QString>(QString("name"), nameInput->text()));

    return data;
}