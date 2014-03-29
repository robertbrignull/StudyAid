#pragma once

#include <QWidget>

class ResizableStackedWidget;
class Model;

class ProofPage : public QWidget
{
    Q_OBJECT

public:
    ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);
};