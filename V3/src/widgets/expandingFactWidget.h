#pragma once

#include <QWidget>
#include <QString>
#include <QPixmap>

class QVBoxLayout;
class QMouseEvent;

class ExpandingFactWidget : public QWidget
{
    Q_OBJECT

public:
    ExpandingFactWidget(int id, QString title, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void setExpanded(bool expanded);



    int id;
    QString title;
    QPixmap image, scaledImage;
    bool expanded;
    int currentHeight;

    QWidget *headWidget;

    int radius, border;
    QColor headColor, bodyColor, borderColor;
};