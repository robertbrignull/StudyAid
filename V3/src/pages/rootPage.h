#pragma once

#include <QWidget>

class QPushButton;
class ResizableStackedWidget;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, QWidget *parent = 0);

private:
    ResizableStackedWidget *newCourseStack;
    ResizableStackedWidget *pageStack;
};