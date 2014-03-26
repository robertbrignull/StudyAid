#pragma once

#include <QSplitter>
#include <QSplitterHandle>

class QResizeEvent;
class QPaintEvent;
class ImageButton;

class Splitter : public QSplitter
{
    Q_OBJECT

public:
    Splitter(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    QSplitterHandle *createHandle();
};

class SplitterHandle : public QSplitterHandle
{
    Q_OBJECT

public:
    SplitterHandle(Qt::Orientation orientation, QSplitter *splitter);

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void layoutButtons();



    ImageButton *expandButton, *collapseButton;
};