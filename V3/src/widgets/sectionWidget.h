#pragma once

#include <iostream>

#include <QWidget>

class SectionWidget : public QWidget
{
    Q_OBJECT

public:
    SectionWidget(int id, std::string title, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

signals:
    void viewButtonClicked(int id);
};