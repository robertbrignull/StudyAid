#include <iostream>

#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>

#include "widgets/imageButton.h"

#include "widgets/expandingFactWidget.h"

ExpandingFactWidget::ExpandingFactWidget(int id, QString title, QWidget *parent)
    : QWidget(parent)
{
    this->id = id;
    this->title = title;

    this->headColor = QColor(66, 139, 202);
    bodyColor = Qt::white;
    borderColor = QColor(66, 139, 202);
    radius = 4;
    border = 16;

    image = QPixmap("images/latex/test.png");
    scaledImage = image.scaledToWidth(size().width() - border*2, Qt::SmoothTransformation);
    expanded = false;



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
    headWidget->setGeometry(0, 0, size().width(), headWidget->sizeHint().height());



    setFixedHeight(headWidget->sizeHint().height());
}

void ExpandingFactWidget::setExpanded(bool expanded)
{
    if (expanded && !this->expanded) {
        this->expanded = true;

        setFixedHeight(headWidget->sizeHint().height() + scaledImage.height() + border*2);
        repaint();
    }
    else if (!expanded && this->expanded) {
        this->expanded = false;

        setFixedHeight(headWidget->sizeHint().height());
        repaint();
    }
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

    painter.drawPixmap(QRect(border, headSize.height() + border, totalSize.width() - border*2, totalSize.height() - headSize.height() - border*2), scaledImage, scaledImage.rect());
}