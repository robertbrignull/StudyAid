#pragma once

#include <QWidget>

class QPushButton;
class ResizableStackedWidget;
class CourseAddPage;
class QDialog;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, QWidget *parent = 0);

private:
    ResizableStackedWidget *pageStack;
    
    QDialog *courseAddDialog;
};