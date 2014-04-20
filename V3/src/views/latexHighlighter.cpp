#include <iostream>

#include "views/latexHighlighter.h"

LatexHighlighter::LatexHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    mathModeFormat.setForeground(QColor("#996600"));
    argumentFormat.setForeground(QColor("#B84A00"));
    bracketFormat.setForeground(QColor("#003366"));
    backSlashFormat.setForeground(QColor("#681F68"));

    rule.pattern = QRegExp("\\[.*\\]|\\{.*\\}");
    rule.pattern.setMinimal(true);
    rule.format = argumentFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\[|\\]|\\(|\\)|\\{|\\}");
    rule.format = bracketFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\\\[A-Za-z]*");
    rule.format = backSlashFormat;
    highlightingRules.append(rule);

    mathModeStartExpression = QRegExp("\\$");
    mathModeEndExpression = QRegExp("[^\\$]\\$+");
}

void LatexHighlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = mathModeStartExpression.indexIn(text);
    }

    while (startIndex >= 0) {
        int endIndex = mathModeEndExpression.indexIn(text, startIndex);
        int length;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            length = text.length() - startIndex;
        }
        else {
            length = endIndex - startIndex + mathModeEndExpression.matchedLength();
        }

        setFormat(startIndex, length, mathModeFormat);
        startIndex = mathModeStartExpression.indexIn(text, startIndex + length);
    }
}