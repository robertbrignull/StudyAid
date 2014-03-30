#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QVariantAnimation>

#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"

#include "widgets/expandingFactWidget.h"

ExpandingFactWidget::ExpandingFactWidget(int id, std::string title, QWidget *parent)
    : QWidget(parent)
{
    headColor = QColor(66, 139, 202);
    bodyColor = Qt::white;
    borderColor = QColor(66, 139, 202);
    radius = 4;
    border = 16;

    expanded = false;
    currentHeight = 0.0;



    headWidget = new QWidget();
    QHBoxLayout *headLayout = new QHBoxLayout(headWidget);
    headLayout->setContentsMargins(16, 8, 16, 8);

    QLabel *label = new QLabel(QString::fromStdString(title));
    label->setWordWrap(true);

    QFont font = label->font();
    font.setPointSize(18);
    label->setFont(font);

    QPalette pal = label->palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    label->setPalette(pal);

    ImageButton *viewButton = new ImageButton(QPixmap(":/images/arrow_right_white.png"), QSize(24, 24));

    headLayout->addWidget(label);
    headLayout->addStretch(1);
    headLayout->addWidget(viewButton);

    headWidget->setParent(this);
    headWidget->show();

    headWidgetHeight = headWidget->sizeHint().height();
    headWidget->setGeometry(0, 0, size().width(), headWidgetHeight);

    image = new ResizableImage("images/latex/test.png", this);
    image->setWidth(size().width() - border*2);
    image->setGeometry((size().width() - image->sizeHint().width()) / 2, headWidgetHeight + border, image->sizeHint().width(), image->sizeHint().height());



    setFixedHeight(headWidgetHeight + (image->sizeHint().height() + border*2) * currentHeight);



    connect(viewButton, &ImageButton::clicked, [=](){
        emit viewButtonClicked(id);
    });
}

void ExpandingFactWidget::setExpanded(bool expanded)
{
    if (expanded != this->expanded) {
        this->expanded = expanded;

        QVariantAnimation *animation = new QVariantAnimation(this);
        animation->setStartValue((expanded) ? 0.0 : 1.0);
        animation->setEndValue((expanded) ? 1.0 : 0.0);
        animation->setDuration(250);
        animation->setEasingCurve(QEasingCurve::InOutCubic);

        connect(animation, &QVariantAnimation::valueChanged, [=](QVariant value){
            currentHeight = value.toFloat();
            setFixedHeight(headWidgetHeight + (image->sizeHint().height() + border*2) * currentHeight);
            repaint();
        });

        animation->start();
    }
}

void ExpandingFactWidget::resizeEvent(QResizeEvent *event)
{
    headWidget->setGeometry(0, 0, event->size().width(), headWidgetHeight);

    image->setWidth(size().width() - border*2);
    image->setGeometry((size().width() - image->sizeHint().width()) / 2, headWidgetHeight + border, image->sizeHint().width(), image->sizeHint().height());

    setFixedHeight(headWidgetHeight + (image->sizeHint().height() + border*2) * currentHeight);
}

void ExpandingFactWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= headWidgetHeight) {
        setExpanded(!expanded);
    }
}

void ExpandingFactWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QSize headSize = headWidget->size();
    QSize totalSize = size();

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QBrush(borderColor), 1));
    painter.setBrush(QBrush(bodyColor));
    painter.drawRoundedRect(1, headSize.height()-radius*2, totalSize.width()-2, totalSize.height()-headSize.height()+radius*2-2, radius, radius);

    painter.setPen(QPen(QBrush(borderColor), 1));
    painter.setBrush(QBrush(headColor));
    painter.drawRoundedRect(1, 1, totalSize.width()-2, headSize.height()-2, radius, radius);
}