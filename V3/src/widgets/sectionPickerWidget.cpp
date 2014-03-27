#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "clickableQLabel.h"
#include "imageButton.h"

#include "sectionPickerWidget.h"

SectionPickerWidget::SectionPickerWidget(int id, QString courseName, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *courseLayout = new QHBoxLayout();
    ClickableQLabel *courseLabel = new ClickableQLabel(courseName);
    ImageButton *courseImage = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(24, 24));

    courseLayout->addWidget(courseLabel);
    courseLayout->addStretch(1);
    courseLayout->addWidget(courseImage);


    
    QHBoxLayout *sec1Layout = new QHBoxLayout();
    ClickableQLabel *sec1Label = new ClickableQLabel("Section 1");
    ImageButton *sec1Image = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(24, 24));

    sec1Layout->addWidget(sec1Label);
    sec1Layout->addStretch(1);
    sec1Layout->addWidget(sec1Image);



    QHBoxLayout *sec2Layout = new QHBoxLayout();
    ClickableQLabel *sec2Label = new ClickableQLabel("Section 2");
    ImageButton *sec2Image = new ImageButton(QPixmap(":/images/plus_black.png"), QSize(24, 24));

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

    });

    connect(sec1Image, &ImageButton::clicked, [=](){

    });

    connect(sec2Image, &ImageButton::clicked, [=](){

    });
}