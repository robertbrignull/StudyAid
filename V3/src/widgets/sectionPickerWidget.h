#pragma once

#include <iostream>

#include "database/structures.h"

#include <QWidget>

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(int id, std::string name, QWidget *parent = 0);

signals:
    void sectionSelected(int id);
    void factAdded(Fact fact);
};