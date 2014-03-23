#pragma once

#include <QWidget>
#include <QString>

class QStackedLayout;

class CourseAddPage : public QWidget
{
    Q_OBJECT

public:
    CourseAddPage(QWidget *parent = 0);

signals:
    void courseAdded(int id);
    void cancelled();
};