#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QVariantAnimation>

#include "widgets/imageButton.h"

#include "widgets/expandingFactWidget.h"

ExpandingFactWidget::ExpandingFactWidget(int id, QString title, QWidget *parent)
    : QWidget(parent)
{
    this->id = id;
    this->title = title;

    headColor = QColor(66, 139, 202);
    bodyColor = Qt::white;
    borderColor = QColor(66, 139, 202);
    radius = 4;
    border = 16;

    image = QPixmap("images/latex/test.png");
    scaledImage = image.scaledToWidth(size().width() - border*2, Qt::SmoothTransformation);
    expanded = false;
    currentHeight = 0;



    headWidget = new QWidget();
    QHBoxLayout *headLayout = new QHBoxLayout(headWidget);
    headLayout->setContentsMargins(16, 8, 16, 8);

    QLabel *label = new QLabel(title);
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



    setFixedHeight(headWidgetHeight + currentHeight);
}

void ExpandingFactWidget::setExpanded(bool expanded)
{
    if (expanded != this->expanded) {
        this->expanded = expanded;

        QVariantAnimation *animation = new QVariantAnimation(this);
        animation->setStartValue(currentHeight);
        animation->setEndValue((expanded) ? scaledImage.height() + border*2 : 0);
        animation->setDuration(250);
        animation->setEasingCurve(QEasingCurve::InOutCubic);

        connect(animation, &QVariantAnimation::valueChanged, [=](QVariant value){
            currentHeight = value.toInt();
            setFixedHeight(headWidgetHeight + currentHeight);
            repaint();
        });

        animation->start();
    }
}

void ExpandingFactWidget::resizeEvent(QResizeEvent *event)
{
    headWidget->setGeometry(0, 0, event->size().width(), headWidgetHeight);
}

void ExpandingFactWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
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

    if (scaledImage.width() != totalSize.width() - border*2) {
        scaledImage = image.scaledToWidth(totalSize.width() - border*2, Qt::SmoothTransformation);
    }

    if (currentHeight > border + 3) {
        QRect destRect = QRect(border, headSize.height() + border, totalSize.width() - border*2, std::min(currentHeight - border - 3, scaledImage.height()));
        QRect srcRect = QRect(0, 0, scaledImage.width(), std::min(currentHeight - border - 3, scaledImage.height()));
        painter.drawPixmap(destRect, scaledImage, srcRect);
    }
}