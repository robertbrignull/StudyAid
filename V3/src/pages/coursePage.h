#pragma once

#include <QWidget>

class ResizableStackedWidget;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, QWidget *parent = 0);

private:
    ResizableStackedWidget *pageStack;
};