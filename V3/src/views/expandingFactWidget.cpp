#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QVariantAnimation>

#include "model.h"
#include "latex/latex.h"
#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"
#include "widgets/resizableStackedWidget.h"

#include "views/expandingFactWidget.h"

ExpandingFactWidget::ExpandingFactWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;
    this->fact = fact;

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

    nameLabel = new QLabel(QString::fromStdString(fact.name));
    nameLabel->setWordWrap(true);

    QFont font = nameLabel->font();
    font.setPointSize(18);
    nameLabel->setFont(font);

    QPalette pal = nameLabel->palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    nameLabel->setPalette(pal);

    ImageButton *viewButton = new ImageButton(QPixmap(":/images/arrow_right_white.png"), QSize(24, 24));

    headLayout->addWidget(nameLabel);
    headLayout->addStretch(1);
    headLayout->addWidget(viewButton);

    headWidget->setParent(this);
    headWidget->show();

    headWidgetHeight = headWidget->sizeHint().height();
    headWidget->setGeometry(0, 0, size().width(), headWidgetHeight);

    image = new ResizableImage(getFactImageFilename(fact), this);
    image->setWidth(size().width() - border*2);
    image->setGeometry((size().width() - image->sizeHint().width()) / 2, headWidgetHeight + border, image->sizeHint().width(), image->sizeHint().height());



    setFixedHeight(headWidgetHeight + (image->sizeHint().height() + border*2) * currentHeight);



    connect(viewButton, SIGNAL(clicked()), this, SLOT(viewButtonClicked()));
    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
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

void ExpandingFactWidget::viewButtonClicked()
{
    model->setFactSelected(fact);
    pageStack->setCurrentIndex(2);
}

void ExpandingFactWidget::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;
        nameLabel->setText(QString::fromStdString(fact.name));
        image->reloadImage();
        adjustSize();
    }
}