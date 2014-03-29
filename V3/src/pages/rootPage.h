#pragma once

#include <map>

#include <QWidget>

class ResizableStackedWidget;
class Model;
class QVBoxLayout;
class CourseTitleWidget;

class RootPage : public QWidget
{
    Q_OBJECT

public:
    RootPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent = 0);

private:
    QVBoxLayout *scrollLayout;
    std::map<int, std::pair<CourseTitleWidget*, int> > courseWidgetMap;
};