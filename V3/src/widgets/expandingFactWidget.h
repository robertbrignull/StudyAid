#pragma once

#include <QWidget>
#include <QString>
#include <QPixmap>

class QMouseEvent;

class ExpandingFactWidget : public QWidget
{
    Q_OBJECT

public:
    ExpandingFactWidget(int id, QString title, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:
    void viewButtonClicked();

private:
    void setExpanded(bool expanded);



    int id;
    QString title;
    QPixmap image, scaledImage;
    bool expanded;
    double currentHeight;

    QWidget *headWidget;
    int headWidgetHeight;

    int radius, border;
    QColor headColor, bodyColor, borderColor;
};