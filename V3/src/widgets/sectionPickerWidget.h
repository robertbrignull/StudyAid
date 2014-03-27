#pragma once

#include <QWidget>
#include <QString>

class FormDialog;

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(int id, QString courseName, FormDialog *factAddDialog, QWidget *parent = 0);

signals:
    void sectionSelected(int id);
    void factAdded(int id);
};