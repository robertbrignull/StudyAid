#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QPainter>
#include <QLabel>

#include "widgets/imageButton.h"

#include "views/courseTitleWidget.h"

CourseTitleWidget::CourseTitleWidget(Course course, QWidget *parent)
    : QWidget(parent)
{
    this->course = course;

    headColor = QColor(66, 139, 202);
    borderColor = QColor(66, 139, 202);
    radius = 4;



    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 8, 16, 8);

    QLabel *label = new QLabel(QString::fromStdString(course.name));
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
    layout->addWidget(viewButton);



    connect(viewButton, SIGNAL(clicked()), this, SLOT(viewButtonClickedSlot()));
}

void CourseTitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QBrush(borderColor), 1));
    painter.setBrush(QBrush(headColor));
    painter.drawRoundedRect(1, 1, size().width()-2, size().height()-2, radius, radius);
}

void CourseTitleWidget::viewButtonClickedSlot()
{
    emit viewButtonClicked(course);
}