#include <iostream>

#include <QtTest/QtTest>

#include "test/course.h"
#include "test/fact.h"

#include "test/runner.h"

void runAllTests()
{
    CourseTest courseTest;
    QTest::qExec(&courseTest);

    FactTest factTest;
    QTest::qExec(&factTest);
}