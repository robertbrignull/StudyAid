#include <iostream>
#include <map>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

#include "widgets/clickableQLabel.h"
#include "widgets/imageButton.h"
#include "dialogs/formDialog.h"

#include "widgets/sectionPickerWidget.h"

SectionPickerWidget::SectionPickerWidget(int id, QString courseName, FormDialog *factAddDialog, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *courseLayout = new QHBoxLayout();
    ClickableQLabel *courseLabel = new ClickableQLabel(courseName);
    ImageButton *courseImage = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(16, 16));

    courseLayout->addWidget(courseLabel);
    courseLayout->addStretch(1);
    courseLayout->addWidget(courseImage);


    
    QHBoxLayout *sec1Layout = new QHBoxLayout();
    ClickableQLabel *sec1Label = new ClickableQLabel("Section 1");
    ImageButton *sec1Image = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(16, 16));

    sec1Layout->addWidget(sec1Label);
    sec1Layout->addStretch(1);
    sec1Layout->addWidget(sec1Image);



    QHBoxLayout *sec2Layout = new QHBoxLayout();
    ClickableQLabel *sec2Label = new ClickableQLabel("Section 2");
    ImageButton *sec2Image = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(16, 16));

    sec2Layout->addWidget(sec2Label);
    sec2Layout->addStretch(1);
    sec2Layout->addWidget(sec2Image);



    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(courseLayout);
    layout->addLayout(sec1Layout);
    layout->addLayout(sec2Layout);



    connect(courseLabel, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(id);
    });

    connect(sec1Label, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(1);
    });

    connect(sec2Label, &ClickableQLabel::clicked, [=](){
        emit sectionSelected(3);
    });



    connect(courseImage, &ImageButton::clicked, [=](){
        factAddDialog->show();
    });

    connect(sec1Image, &ImageButton::clicked, [=](){
        factAddDialog->show();
    });

    connect(sec2Image, &ImageButton::clicked, [=](){
        factAddDialog->show();
    });
}