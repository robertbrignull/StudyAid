#pragma once

#include <QWidget>
#include <QString>

class SectionPickerWidget : public QWidget
{
    Q_OBJECT

public:
    SectionPickerWidget(int id, QString courseName, QWidget *parent = 0);

signals:
    void sectionSelected(int id);
    void factAdded(int id);
};