#pragma once

#include <QWidget>

class DependenciesWidget : public QWidget
{
    Q_OBJECT;

public:
    DependenciesWidget(QWidget *parent = 0);

signals:
    void viewButtonClicked(int id);

private:
    int depBeingDeleted;
};