#include <iostream>

#include <QPainter>

#include "widgets/trafficLight.h"

TrafficLight::TrafficLight(int initialState, QWidget *parent)
    : QWidget(parent)
{
    state = initialState;
}

int TrafficLight::getState()
{
    return state;
}

void TrafficLight::setState(int state)
{
    this->state = state;
    repaint();
}

void TrafficLight::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor color;
    if (state == TrafficLight::RED)   color = Qt::red;
    if (state == TrafficLight::AMBER) color = Qt::yellow;
    if (state == TrafficLight::GREEN) color = Qt::green;

    painter.setBrush(QBrush(QColor(color)));

    painter.drawEllipse(width()/2 - 6, height()/2 - 6, 12, 12);
}