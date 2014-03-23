#pragma once

#include <QWidget>

class QVBoxLayout;
class QMouseEvent;

class ExpandingWidget : public QWidget
{
    Q_OBJECT

public:
    ExpandingWidget(QWidget *head, QWidget *body, QWidget *parent = 0);

    QWidget *getHead();
    QWidget *getBody();

    void setHead(QWidget *head);
    void setBody(QWidget *body);

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void createLayout(QWidget *head, QWidget *body, bool expanded);
    void setExpanded(bool expanded);



    QVBoxLayout *layout;
    QWidget *head, *body;
    bool expanded;

    int radius;
    QColor headColor, bodyColor, borderColor;
};