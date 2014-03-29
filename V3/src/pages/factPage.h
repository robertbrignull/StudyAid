#pragma once

#include <QWidget>

class ResizableStackedWidget;
class Model;

class FactPage : public QWidget
{
    Q_OBJECT

public:
    FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);
};