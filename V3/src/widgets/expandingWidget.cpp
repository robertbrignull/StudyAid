#include <iostream>

#include <QVBoxLayout>
#include <QMouseEvent>

#include "widgets/expandingWidget.h"

ExpandingWidget::ExpandingWidget(QWidget *head, QWidget *body, QWidget *parent)
    : QWidget(parent)
{
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