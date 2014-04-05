#include <iostream>
#include <map>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "dialogs/formDialog.h"
#include "dialogs/deleteDialog.h"
#include "forms/courseForm.h"
#include "forms/factForm.h"
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
    const char *newFactType = "Axiom";

    // Add our course
    TestUtil::addCourse(window, newCourseName);

    // Check that no facts are shown
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Add our fact
    TestUtil::addFact(window, newFactName, newFactType);

    // Check that we're on the fact page
    QVERIFY(window->stack->currentIndex() == 2);

    // Check that the name is shown correctly on the fact page
    QVERIFY(factPage->factLabel->text() == newFactName);
    QVERIFY(factPage->breadCrumbs->currentFactLabel->text() == newFactName);

    // Check that the name and type are correct in the editFactDialog
    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);
    QVERIFY(factPage->factEditForm->nameInput->text() == newFactName);
    QVERIFY(factPage->factEditForm->typeInput->currentText() == newFactType);
    QTest::mouseClick(factPage->factEditDialog->cancelButton, Qt::LeftButton);

    // Check that the course page shows one fact
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 1);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == newFactName);
}

void FactTest::test_addFact_canHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *newCourseName = "Set Theory";
    const char *newFactName = "The empty set is unique";
    const char *newFactType = "Theorem";
    const bool newFactCanHaveType = true;

    // Add our course and fact
    TestUtil::addCourse(window, newCourseName);
    TestUtil::addFact(window, newFactName, newFactType);

    // Check that the proofs section of the splitter is shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == newFactCanHaveType);

    // Check that the AddProofButton is shown
    QVERIFY(factPage->addProofButton->isVisible() == newFactCanHaveType);
}

void FactTest::test_addFact_canNotHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *newCourseName = "Set Theory";
    const char *newFactName = "ZF1 - Extensionality";
    const char *newFactType = "Axiom";
    const bool newFactCanHaveType = false;

    // Add our course and fact
    TestUtil::addCourse(window, newCourseName);
    TestUtil::addFact(window, newFactName, newFactType);

    // Check that the proofs section of the splitter is not shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == newFactCanHaveType);

    // Check that the AddProofButton is not shown
    QVERIFY(factPage->addProofButton->isVisible() == newFactCanHaveType);
}

void FactTest::test_editFact()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *newCourseName = "Set Theory";
    const char *oldFactName = "ZF1 - Extensionality";
    const char *oldFactType = "Axiom";
    const char *newFactName = "The empty set is unique";
    const char *newFactType = "Theorem";

    // Add our course and fact
    TestUtil::addCourse(window, newCourseName);
    TestUtil::addFact(window, oldFactName, oldFactType);

    // Immediately change the fact's name and type
    TestUtil::editCurrentFact(window, newFactName, newFactType);

    // Check that the name is shown correctly on the fact page
    QVERIFY(factPage->factLabel->text() == newFactName);
    QVERIFY(factPage->breadCrumbs->currentFactLabel->text() == newFactName);

    // Check that the name and type are correct in the editFactDialog
    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);
    QVERIFY(factPage->factEditForm->nameInput->text() == newFactName);
    QVERIFY(factPage->factEditForm->typeInput->currentText() == newFactType);
    QTest::mouseClick(factPage->factEditDialog->cancelButton, Qt::LeftButton);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == newFactName);
}

void FactTest::test_editFact_canHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *newCourseName = "Set Theory";
    const char *oldFactName = "ZF1 - Extensionality";
    const char *oldFactType = "Axiom";
    const char *newFactName = "The empty set is unique";
    const char *newFactType = "Theorem";
    const bool newFactCanHaveType = true;

    // Add our course and fact
    TestUtil::addCourse(window, newCourseName);
    TestUtil::addFact(window, oldFactName, oldFactType);

    // Immediately change the fact's name and type
    TestUtil::editCurrentFact(window, newFactName, newFactType);

    // Check that the proofs section of the splitter is shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == newFactCanHaveType);

    // Check that the AddProofButton is shown
    QVERIFY(factPage->addProofButton->isVisible() == newFactCanHaveType);
}

void FactTest::test_editFact_canNotHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *newCourseName = "Set Theory";
    const char *oldFactName = "The empty set is unique";
    const char *oldFactType = "Theorem";
    const char *newFactName = "ZF1 - Extensionality";
    const char *newFactType = "Axiom";
    const bool newFactCanHaveType = false;

    // Add our course and fact
    TestUtil::addCourse(window, newCourseName);
    TestUtil::addFact(window, oldFactName, oldFactType);

    // Immediately change the fact's name and type
    TestUtil::editCurrentFact(window, newFactName, newFactType);

    // Check that the proofs section of the splitter is shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == newFactCanHaveType);

    // Check that the AddProofButton is shown
    QVERIFY(factPage->addProofButton->isVisible() == newFactCanHaveType);
}

void FactTest::test_deleteFact()
{
    CoursePage *coursePage = window->coursePage;

    const char *newCourseName = "Set Theory";
    const char *newFactName = "ZF1 - Extensionality";
    const char *newFactType = "Axiom";

    // Add our course and fact
    TestUtil::addCourse(window, newCourseName);
    TestUtil::addFact(window, newFactName, newFactType);

    // Immediately delete the fact
    TestUtil::deleteCurrentFact(window);

    // Check that no facts are shown
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);
}