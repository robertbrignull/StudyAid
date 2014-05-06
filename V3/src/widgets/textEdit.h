#pragma once

#include <QTextEdit>

class QKeyEvent;

class TextEdit : public QTextEdit
{
    Q_OBJECT

signals:
    void keyPress();

public:
    void keyPressEvent(QKeyEvent *event);
};