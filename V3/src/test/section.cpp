#include <iostream>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "forms/courseForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/clickableQLabel.h"
#include "widgets/dialog.h"
#include "views/breadCrumbs.h"
#include "views/courseTitleWidget.h"
#include "views/factListView.h"
#include "views/factList.h"
#include "views/sectionPickerWidget.h"
#include "views/expandingFactWidget.h"

#include "test/testUtil.h"

#include "test/section.h"

void SectionTest::init()
{
    clearTestDatabase();

    window = new StudyAid();
}

void SectionTest::cleanup()
{
    delete window;
}

void SectionTest::test_addSection_toRoot()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";

    // Add our course
    TestUtil::addCourse(window, courseName);

    // Check that the fact list is still empty
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Check that the root section has the correct label
    QVERIFY(coursePage->sectionPicker->sectionLabel->text() == "All");

    // Add our new section
    TestUtil::addFact(window, sectionName, "Section");

    // Check that the new section is shown in the section picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 1);

    // Check it has the correct name
    auto sectionPicker = coursePage->sectionPicker->idSectionPickerMap.begin()->second.second;
    QVERIFY(sectionPicker->sectionLabel->text() == sectionName);

    // Check that the new section has no children
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 0);

    // Check that the fact list has updated
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->idChildMap.size() == 1);

    // Check that the section in the fact list has the correct name and no children
    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == sectionName);
    QVERIFY(factList->idChildMap.size() == 0);
}

void SectionTest::test_addSection_toSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *parentSectionName = "Cardinal Numbers";
    const char *childSectionName = "Infinities";

    // Add our course and sections
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, parentSectionName, "Section");
    TestUtil::addFactToSection(window, childSectionName, "Section", parentSectionName);

    // Check that each section has the correct name and number of children
    auto sectionPicker = coursePage->sectionPicker;

    QVERIFY(sectionPicker->sectionLabel->text() == "All");
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 1);

    sectionPicker = sectionPicker->idSectionPickerMap.begin()->second.second;

    QVERIFY(sectionPicker->sectionLabel->text() == parentSectionName);
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 1);

    sectionPicker = sectionPicker->idSectionPickerMap.begin()->second.second;

    QVERIFY(sectionPicker->sectionLabel->text() == childSectionName);
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 0);

    // Check that the fact list is correct
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->idChildMap.size() == 1);

    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == parentSectionName);
    QVERIFY(factList->idChildMap.size() == 1);

    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == childSectionName);
    QVERIFY(factList->idChildMap.size() == 0);
}

void SectionTest::test_selectSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";
    const char *level0FactName = "level 0 fact";
    const char *level0FactType = "Theorem";
    const char *level1FactName = "level 1 fact";
    const char *level1FactType = "Theorem";

    // Add our course and sections and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, level0FactName, level0FactType);
    TestUtil::addFact(window, sectionName, "Section");
    TestUtil::addFactToSection(window, level1FactName, level1FactType, sectionName);

    // Select the section
    TestUtil::selectSection(window, sectionName);

    // Check that the fact list has 1 element
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 1);

    // Check that that element has the correct name
    ExpandingFactWidget *factWidget = (ExpandingFactWidget*) coursePage->factListView->currentFactList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == level1FactName);

    // Select the root section again
    TestUtil::selectSection(window, "All");

    // Check that the fact list now has two elements, one of which is a section
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->idChildMap.size() == 2);
    QVERIFY(factList->idChildSectionMap.size() == 1);

    // Check that the first element is not a section
    auto childIt = factList->idChildMap.begin();
    auto sectionIt = factList->idChildSectionMap.begin();
    QVERIFY(childIt->second.second != sectionIt->second.second);

    // Check that the first element is a fact of the correct name
    factWidget = (ExpandingFactWidget*) childIt->second.second;
    QVERIFY(factWidget->nameLabel->text() == level0FactName);

    // Check that the second is a section
    childIt++;
    QVERIFY(childIt->second.second == sectionIt->second.second);

    // Check that the section has the correct name
    factList = sectionIt->second.second;
    QVERIFY(factList->sectionNameLabel->text() == sectionName);

    // Check that the section has one child which is not a section
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 0);

    // Check that the first element is a fact of the correct name
    factWidget = (ExpandingFactWidget*) factList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == level1FactName);
}

void SectionTest::test_editSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";
    const char *newSectionName = "Infinities";

    // Add our course and section
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName, "Section");

    // Immediately change the name to something else
    TestUtil::editSection(window, newSectionName, sectionName);

    // Check that the new section is shown in the section picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 1);

    // Check it has the correct name
    auto sectionPicker = coursePage->sectionPicker->idSectionPickerMap.begin()->second.second;
    QVERIFY(sectionPicker->sectionLabel->text() == newSectionName);

    // Check that the new section has no children
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 0);

    // Check that the fact list has updated
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->idChildMap.size() == 1);

    // Check that the section in the fact list has the correct name and no children
    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == newSectionName);
    QVERIFY(factList->idChildMap.size() == 0);
}

void SectionTest::test_deleteSection_empty()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";

    // Add our course and section
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName, "Section");

    // Immediately delete the section
    TestUtil::deleteSection(window, sectionName);

    // Check that the course page shows no facts
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Check that the no sections are shown in the picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 0);
}

void SectionTest::test_deleteSection_notEmpty()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";
    const char *level0FactName = "level 0 fact";
    const char *level0FactType = "Theorem";
    const char *level1FactName = "level 1 fact";
    const char *level1FactType = "Theorem";

    // Add our course and section and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, level0FactName, level0FactType);
    TestUtil::addFact(window, sectionName, "Section");
    TestUtil::addFactToSection(window, level1FactName, level1FactType, sectionName);

    // Immediately delete the section
    TestUtil::deleteSection(window, sectionName);

    // Check that the course page shows one fact
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 1);

    // Check that the fact is the correct one
    ExpandingFactWidget *factWidget = (ExpandingFactWidget*) coursePage->factListView->currentFactList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == level0FactName);

    // Check that the no sections are shown in the picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 0);
}