#pragma once

#include <QWidget>

class ResizableStackedWidget;

class ProofPage : public QWidget
{
    Q_OBJECT

public:
    ProofPage(ResizableStackedWidget *pageStack, QWidget *parent = 0);
};