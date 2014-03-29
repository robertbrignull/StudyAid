#pragma once

#include <iostream>

#include <QWidget>
#include <QPixmap>

class CourseTitleWidget : public QWidget
{
    Q_OBJECT

public:
    CourseTitleWidget(std::string name, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

signals:
    void viewButtonClicked();

private:
    int radius;
    QColor headColor, borderColor;
};