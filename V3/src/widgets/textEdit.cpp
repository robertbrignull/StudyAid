#include <iostream>

#include <QKeyEvent>

#include "widgets/textEdit.h"

void TextEdit::keyPressEvent(QKeyEvent *event)
{
    QTextEdit::keyPressEvent(event);

    emit keyPress();
}