#include <iostream>

#include <QtTest/QtTest>

#include "test/course.h"
#include "test/fact.h"
#include "test/proof.h"
#include "test/section.h"

#include "test/runner.h"

void runAllTests()
{
    CourseTest courseTest;
    QTest::qExec(&courseTest);

    FactTest factTest;
    QTest::qExec(&factTest);

    ProofTest proofTest;
    QTest::qExec(&proofTest);

    SectionTest sectionTest;
    QTest::qExec(&sectionTest);
}