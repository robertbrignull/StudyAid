#pragma once

#include <QStackedWidget>

class ResizableStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    virtual void addWidget(QWidget* pWidget);

public slots:
    void onCurrentChanged(int index);
};