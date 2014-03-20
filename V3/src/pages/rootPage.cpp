#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>

#include "pages/rootPage.h"

RootPage::RootPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);



    QLabel *titleLabel = new QLabel("Study Aid");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(72);
    titleFont.setBold(true);
    titleFont.setUnderline(true);
    titleLabel->setFont(titleFont);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addStretch(1);
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch(1);
    layout->addLayout(titleLayout);



    layout->addStretch(1);
}