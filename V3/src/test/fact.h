#pragma once

#include <QObject>

class StudyAid;

class FactTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

private:
    StudyAid *window;
};