#include <iostream>

#include "views/latexHighlighter.h"

LatexHighlighter::LatexHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    yellow = QColor("#996600");
    orange = QColor("#B84A00");
    blue = QColor("#003366");
    purple = QColor("#681F68");

    backslashColor = purple;
    argumentColor = orange;
    bracketColor = blue;
    mathMathColor = yellow;

    // Math mode start and end expressions
    mathModeStartPattern = QRegExp("\\$");
    mathModeEndPattern = QRegExp("[^\\$]\\$+");

    // Other expressions
    backslashPattern = QRegExp("\\\\[A-Za-z]+|\\\\\\{|\\\\\\}");

    argumentPattern = QRegExp("[\\{\\[].*[\\}\\]]");
    argumentPattern.setMinimal(true);

    bracketPattern = QRegExp("\\[|\\]|\\{|\\}|\\(|\\)");

    mathModeBoundaryPattern = QRegExp("\\$+|\\\\\\(|\\\\\\)|\\\\\\[|\\\\\\]");
}

void LatexHighlighter::highlightBlock(const QString &text)
{
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = mathModeStartPattern.indexIn(text);
    }

    while (startIndex >= 0) {
        int endIndex = mathModeEndPattern.indexIn(text, startIndex);
        int length;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            length = text.length() - startIndex;
        }
        else {
            length = endIndex - startIndex + mathModeEndPattern.matchedLength();
        }

        setFormat(startIndex, length, yellow);

        startIndex = mathModeStartPattern.indexIn(text, startIndex + length);
    }



    // Some simple rules
    int bracketStartIndex = bracketPattern.indexIn(text);
    while (bracketStartIndex >= 0) {
        int bracketLength = bracketPattern.matchedLength();
        setFormat(bracketStartIndex, bracketLength, bracketColor);
        bracketStartIndex = bracketPattern.indexIn(text, bracketStartIndex + bracketLength);
    }

    int mathModeBoundaryStartIndex = mathModeBoundaryPattern.indexIn(text);
    while (mathModeBoundaryStartIndex >= 0) {
        int mathModeBoundaryLength = mathModeBoundaryPattern.matchedLength();
        setFormat(mathModeBoundaryStartIndex, mathModeBoundaryLength, mathMathColor);
        mathModeBoundaryStartIndex = mathModeBoundaryPattern.indexIn(text, mathModeBoundaryStartIndex + mathModeBoundaryLength);
    }



    // The idea here is to have a backslash part followed by zero or more arguments
    int backslashStartIndex = backslashPattern.indexIn(text);
    while (backslashStartIndex >= 0) {
        // Work out the length and end point of the backslash part
        int backslashLength = backslashPattern.matchedLength();
        int backslashEndIndex = backslashStartIndex + backslashLength;

        // Set the format of the backslash part
        setFormat(backslashStartIndex, backslashLength, backslashColor);

        // Start on the arguments, only continue while there is no gap
        int argumentStartIndex = argumentPattern.indexIn(text, backslashEndIndex);
        int argumentEndIndex = backslashEndIndex;
        while (argumentStartIndex == argumentEndIndex) {
            // Work out the length and end point of the argument
            int argumentLength = argumentPattern.matchedLength();
            argumentEndIndex = argumentStartIndex + argumentLength;

            // Set the format of the argument
            setFormat(argumentStartIndex, argumentLength, argumentColor);

            // Set the end point and find the next argument
            argumentStartIndex = argumentPattern.indexIn(text, argumentEndIndex);
        }

        // Find the next backslash
        backslashStartIndex = backslashPattern.indexIn(text, backslashEndIndex);
    }
}