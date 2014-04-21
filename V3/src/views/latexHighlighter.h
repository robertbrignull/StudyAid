#pragma once

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegExp>
#include <QTextCharFormat>
#include <QVector>

class LatexHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LatexHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    QRegExp mathModeStartPattern;
    QRegExp mathModeEndPattern;

    QRegExp backslashPattern;
    QRegExp argumentPattern;
    QRegExp bracketPattern;
    QRegExp mathModeBoundaryPattern;

    QColor yellow, orange, blue, purple;
    QColor backslashColor, argumentColor, bracketColor, mathMathColor;
};