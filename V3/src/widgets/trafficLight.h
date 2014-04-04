#pragma once

#include <QWidget>

class QPaintEvent;

class TrafficLight : public QWidget
{
    Q_OBJECT

public:
    TrafficLight(int initialState, QWidget *parent = 0);

    int getState();
    void setState(int state);

    void paintEvent(QPaintEvent *);



    static const int RED = 0;
    static const int AMBER = 1;
    static const int GREEN = 2;

private:
    int state;
};