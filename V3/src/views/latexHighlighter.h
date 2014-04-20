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
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp mathModeStartExpression;
    QRegExp mathModeEndExpression;

    QTextCharFormat mathModeFormat;
    QTextCharFormat argumentFormat;
    QTextCharFormat bracketFormat;
    QTextCharFormat backSlashFormat;
};