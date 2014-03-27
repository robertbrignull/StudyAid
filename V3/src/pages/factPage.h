#pragma once

#include <QWidget>

class ResizableStackedWidget;

class FactPage : public QWidget
{
    Q_OBJECT

public:
    FactPage(ResizableStackedWidget *pageStack, QWidget *parent = 0);
};