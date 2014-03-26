#pragma once

#include <QWidget>
#include <QString>

class SectionWidget : public QWidget
{
    Q_OBJECT

public:
    SectionWidget(int id, QString title, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

signals:
    void viewButtonClicked(int id);
};