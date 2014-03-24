#include <iostream>

#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>

#include "widgets/layout/expandingWidget.h"

ExpandingWidget::ExpandingWidget(QColor headColor, QWidget *head, QWidget *body, QWidget *parent)
    : QWidget(parent)
{
    this->layout = nullptr;
    this->head = this->body = nullptr;
    this->expanded = false;

    this->headColor = headColor;
    bodyColor = Qt::white;
    borderColor = Qt::black;
    radius = 12;

    createLayout(head, body, false);
}

QWidget *ExpandingWidget::getHead()
{
    return head;
}

QWidget *ExpandingWidget::getBody()
{
    return body;
}

void ExpandingWidget::setHead(QWidget *head)
{
    createLayout(head, body, expanded);
}

void ExpandingWidget::setBody(QWidget *body)
{
    createLayout(head, body, expanded);
}

void ExpandingWidget::createLayout(QWidget *head, QWidget *body, bool expanded)
{
    if (layout != nullptr) {
        // Remove all items but don't delete them
        std::cout << "About to delete items from layout" << std::endl;
        while (layout->takeAt(0)) { }

        delete layout;
        layout = nullptr;
    }

    if (this->head != head) {
        delete this->head;
        this->head = head;
    }

    if (this->body != body) {
        delete this->body;
        this->body = body;
    }

    this->expanded = expanded;

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(head);

    if (expanded) {
        layout->addWidget(body);
    }
}

void ExpandingWidget::setExpanded(bool expanded)
{
    if (expanded && !this->expanded) {
        layout->addWidget(body);
        this->expanded = true;
    }
    else if (!expanded && this->expanded) {
        layout->takeAt(1);
        this->expanded = false;
    }
}

void ExpandingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setExpanded(!expanded);
    }
}

void ExpandingWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QSize headSize = head->size();
    QSize totalSize = size();

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QBrush(borderColor), 1));
    painter.setBrush(QBrush(bodyColor));
    painter.drawRoundedRect(1, headSize.height()-radius*2, totalSize.width()-2, totalSize.height()-headSize.height()+radius*2-2, radius, radius);

    painter.setPen(QPen(QBrush(borderColor), 1));
    painter.setBrush(QBrush(headColor));
    painter.drawRoundedRect(1, 1, totalSize.width()-2, headSize.height()-2, radius, radius);
}