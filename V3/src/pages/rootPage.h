#pragma once

#include <QWidget>

class ResizableStackedWidget;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, QWidget *parent = 0);
};