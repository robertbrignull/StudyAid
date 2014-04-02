#pragma once

#include <QObject>

class Test : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testOne();
    void testTwo();
};