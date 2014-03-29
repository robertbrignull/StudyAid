#pragma once

#include <iostream>

#include <QWidget>

class FormDialog;

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(int id, std::string courseName, FormDialog *factAddDialog, QWidget *parent = 0);

signals:
    void sectionSelected(int id);
    void factAdded(int id);
};