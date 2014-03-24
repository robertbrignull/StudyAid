#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QPalette>

#include "widgets/imageButton.h"

#include "widgets/courseTitleWidget.h"

CourseTitleWidget::CourseTitleWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 8, 16, 8);

    QLabel *label = new QLabel("Linear Algebra");
    label->setWordWrap(true);

    QFont font = label->font();
    font.setPointSize(18);
    label->setFont(font);

    QPalette pal = label->palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    label->setPalette(pal);

    ImageButton *viewButton = new ImageButton(QPixmap(":/images/arrow_right_white.png"), QSize(24, 24));

    layout->addWidget(label);
    layout->addStretch(1);
    layout->addWidget(viewButton);
}