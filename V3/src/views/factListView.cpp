#include <QHBoxLayout>

#include "model.h"
#include "database/methods.h"
#include "widgets/resizableStackedWidget.h"
#include "views/factList.h"

#include "views/factListView.h"

FactListView::FactListView(Course course, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->course = course;

    idFactListMap = std::map<int, FactList*>();

    currentFactList = new FactList(findFact(course.root_fact), model, pageStack, this);
    idFactListMap.insert(std::pair<int, FactList*>(course.root_fact, currentFactList));

    currentFactList->buildLayout(true);

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(currentFactList);
}

FactListView::~FactListView()
{
    currentFactList->destroyLayout();

    while (layout->count() > 0) {
        layout->takeAt(0);
    }

    while (idFactListMap.size() > 0) {
        delete idFactListMap.begin()->second;
    }
}

void FactListView::selectSection(int id)
{
    currentFactList->destroyLayout();
    
    while (layout->count() > 0) {
        layout->takeAt(0);
    }

    currentFactList = idFactListMap.at(id);
    currentFactList->buildLayout(true);

    layout->addWidget(currentFactList);
    currentFactList->show();
}