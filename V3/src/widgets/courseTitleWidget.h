#pragma once

#include <QWidget>
#include <QString>
#include <QPixmap>

class CourseTitleWidget : public QWidget
{
    Q_OBJECT

public:
    CourseTitleWidget(int id, QString name, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

private:
    int id;
    QString name;

    int radius;
    QColor headColor, borderColor;
};