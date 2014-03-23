#include <iostream>

#include <QStackedWidget>
#include <QLayout>

#include "widgets/layout/resizableStackedWidget.h"

void ResizableStackedWidget::addWidget(QWidget* pWidget)
{
    pWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QStackedWidget::addWidget(pWidget);
}

void ResizableStackedWidget::onCurrentChanged(int index)
{
    QLayout *l = layout();
    for (int i = 0; i < l->count(); ++i) {
        QSizePolicy::Policy p = (i == index) ? QSizePolicy::Preferred : QSizePolicy::Ignored;
        QWidget *w = l->itemAt(i)->widget();
        w->setSizePolicy(p, p);
        w->adjustSize();
    }

    adjustSize();
}