#include <iostream>
#include <map>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "dialogs/formDialog.h"
#include "dialogs/deleteDialog.h"
#include "forms/courseForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/breadCrumbs.h"
#include "widgets/courseTitleWidget.h"
#include "widgets/factListView.h"
#include "widgets/factList.h"
#include "widgets/expandingFactWidget.h"

#include "test/testUtil.h"

#include "test/fact.h"

void FactTest::init()
{
    clearTestDatabase();

    window = new StudyAid();
}

void FactTest::cleanup()
{
    delete window;
}

void FactTest::test_addFact()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *newCourseName = "Set Theory";
    const char *newFactName = "ZF1 - Extensionality";

    // Add our course
    TestUtil::addCourse(window, newCourseName);

    // Check that no facts are shown
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Add our fact
    TestUtil::addFact(window, newFactName, "Axiom");

    // Check that we're on the fact page
    QVERIFY(window->stack->currentIndex() == 2);

    // Check that the name is shown correctly on the fact page
    QVERIFY(factPage->factLabel->text() == newFactName);
    QVERIFY(factPage->breadCrumbs->currentFactLabel->text() == newFactName);

    // Check that the course page shows one fact
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 1);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == newFactName);
}

void FactTest::test_editFact()
{

}

void FactTest::test_deleteFact()
{

}