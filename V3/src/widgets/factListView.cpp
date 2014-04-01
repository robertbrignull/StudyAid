#include <QHBoxLayout>

#include "model.h"
#include "database/methods.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/factList.h"

#include "widgets/factListView.h"

FactListView::FactListView(Course course, Model *model, ResizableStackedWidget *pageStack, QWidget *parent)
    : QWidget(parent)
{
    this->course = course;

    idFactListMap = std::map<int, FactList*>();

    FactList *rootFactList = new FactList(findFact(course.root_fact), model, pageStack, &idFactListMap);

    layout = new QHBoxLayout(this);

    layout->addWidget(rootFactList);
}

FactListView::~FactListView()
{
    delete idFactListMap.at(course.root_fact);
}

void FactListView::selectSection(int id)
{
    while (layout->count() > 0) {
        layout->takeAt(0)->widget();
    }

    layout->addWidget(idFactListMap.at(id));
}