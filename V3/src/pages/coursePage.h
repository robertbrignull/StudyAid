#pragma once

#include <QWidget>

class ResizableStackedWidget;
class Model;
class QLabel;
class QVBoxLayout;

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    CoursePage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

private:
    QLabel *currentCourseLabel, *courseLabel;
    QVBoxLayout *pickerScrollLayout;
};