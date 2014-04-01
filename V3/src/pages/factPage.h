#pragma once

#include <QWidget>

class ResizableStackedWidget;
class Model;
class ClickableQLabel;
class QLabel;
class QTextEdit;

class FactPage : public QWidget
{
    Q_OBJECT

public:
    FactPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

private:
    ClickableQLabel *factsLabel;
    QLabel *currentFactLabel, *factLabel;
    QTextEdit *statementTextEdit;
};