#include <iostream>

#include <QtTest/QtTest>

#include "test/test.h"

void Test::initTestCase()
{
    
}

void Test::cleanupTestCase()
{

}

void Test::testOne()
{
    QVERIFY(1 == 1);
}

void Test::testTwo()
{
    QVERIFY(1 == 0);
}