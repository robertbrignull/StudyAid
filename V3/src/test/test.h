#pragma once

#include <QObject>

class StudyAid;

class Test : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void testOne();

private:
    StudyAid *window;
};