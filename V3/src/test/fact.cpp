#include <iostream>
#include <map>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>
#include <QTextEdit>
#include <QPixmap>
#include <QImage>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "database/setup.h"
#include "database/methods.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "forms/courseForm.h"
#include "forms/factForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"
#include "widgets/dialog.h"
#include "widgets/splitter.h"
#include "views/breadCrumbs.h"
#include "views/courseTitleWidget.h"
#include "views/factListView.h"
#include "views/factList.h"
#include "views/expandingFactWidget.h"

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

    const char *courseName = "Set Theory";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";

    // Add our course
    TestUtil::addCourse(window, courseName);

    // Check that no facts are shown
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Add our fact
    TestUtil::addFact(window, factName, factType);

    // Check that we're on the fact page
    QVERIFY(window->stack->currentIndex() == 2);

    // Check that the name is shown correctly on the fact page
    QVERIFY(factPage->factLabel->text() == factName);
    QVERIFY(factPage->breadCrumbs->currentFactLabel->text() == factName);

    // Check that the name and type are correct in the editFactDialog
    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);
    QVERIFY(factPage->factEditForm->nameInput->text() == factName);
    QVERIFY(factPage->factEditForm->typeInput->currentText() == factType);
    QTest::mouseClick(factPage->factEditDialog->cancelButton, Qt::LeftButton);

    // Check that the course page shows one fact
    auto currentFactList = coursePage->factListView->currentFactList;
    QVERIFY(currentFactList->layout->count() == 1);
    QVERIFY(currentFactList->idChildMap.size() == 1);
    QVERIFY(currentFactList->idChildSectionMap.size() == 0);
    QVERIFY(currentFactList->idChildFactMap.size() == 1);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == factName);
}

void FactTest::test_addFact_canHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const bool factCanHaveType = true;

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Check that the proofs section of the splitter is shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == factCanHaveType);

    // Check that the AddProofButton is shown
    QVERIFY(factPage->addProofButton->isVisible() == factCanHaveType);
}

void FactTest::test_addFact_canNotHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";
    const bool factCanHaveType = false;

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Check that the proofs section of the splitter is not shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == factCanHaveType);

    // Check that the AddProofButton is not shown
    QVERIFY(factPage->addProofButton->isVisible() == factCanHaveType);
}

void FactTest::test_addFact_multiple()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *otherFactName = "The empty set is unique";
    const char *otherFactType = "Theorem";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";

    // Add our course and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, otherFactName, otherFactType);
    TestUtil::addFact(window, factName, factType);

    // Check that the name is shown correctly on the fact page
    QVERIFY(factPage->factLabel->text() == factName);
    QVERIFY(factPage->breadCrumbs->currentFactLabel->text() == factName);

    // Check that the name and type are correct in the editFactDialog
    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);
    QVERIFY(factPage->factEditForm->nameInput->text() == factName);
    QVERIFY(factPage->factEditForm->typeInput->currentText() == factType);
    QTest::mouseClick(factPage->factEditDialog->cancelButton, Qt::LeftButton);

    // Check that the course page shows one fact
    auto currentFactList = coursePage->factListView->currentFactList;
    QVERIFY(currentFactList->layout->count() == 2);
    QVERIFY(currentFactList->idChildMap.size() == 2);
    QVERIFY(currentFactList->idChildSectionMap.size() == 0);
    QVERIFY(currentFactList->idChildFactMap.size() == 2);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == otherFactName);

    it++;
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == factName);
}

void FactTest::test_editFact()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *oldFactName = "ZF1 - Extensionality";
    const char *oldFactType = "Axiom";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, oldFactName, oldFactType);

    // Immediately change the fact's name and type
    TestUtil::editCurrentFact(window, factName, factType);

    // Check that the name is shown correctly on the fact page
    QVERIFY(factPage->factLabel->text() == factName);
    QVERIFY(factPage->breadCrumbs->currentFactLabel->text() == factName);

    // Check that the name and type are correct in the editFactDialog
    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);
    QVERIFY(factPage->factEditForm->nameInput->text() == factName);
    QVERIFY(factPage->factEditForm->typeInput->currentText() == factType);
    QTest::mouseClick(factPage->factEditDialog->cancelButton, Qt::LeftButton);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == factName);
}

void FactTest::test_editFact_canHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *oldFactName = "ZF1 - Extensionality";
    const char *oldFactType = "Axiom";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const bool factCanHaveType = true;

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, oldFactName, oldFactType);

    // Immediately change the fact's name and type
    TestUtil::editCurrentFact(window, factName, factType);

    // Check that the proofs section of the splitter is shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == factCanHaveType);

    // Check that the AddProofButton is shown
    QVERIFY(factPage->addProofButton->isVisible() == factCanHaveType);
}

void FactTest::test_editFact_canNotHaveProof()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *oldFactName = "The empty set is unique";
    const char *oldFactType = "Theorem";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";
    const bool factCanHaveType = false;

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, oldFactName, oldFactType);

    // Immediately change the fact's name and type
    TestUtil::editCurrentFact(window, factName, factType);

    // Check that the proofs section of the splitter is shown
    QVERIFY(factPage->proofsScrollArea->isVisible() == factCanHaveType);

    // Check that the AddProofButton is shown
    QVERIFY(factPage->addProofButton->isVisible() == factCanHaveType);
}

void FactTest::test_editFact_statement()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";
    const char *shortFactStatement = "Single line";
    const char *longFactStatement = "Multiple\\\\\n... lines!";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Check the statement is empty
    QVERIFY(factPage->statementTextEdit->toPlainText() == "");
    QVERIFY(factPage->statementImage->imageLoaded == false);

    // Change the statement to something short but nonempty
    TestUtil::editCurrentFactStatement(window, shortFactStatement);

    // Check the rendered image is not blank
    QVERIFY(factPage->statementImage->imageLoaded == true);

    // Record the size of the image
    int oldHeightOnFactPage = factPage->statementImage->image.height();

    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    int oldHeightOnCoursePage = ((ExpandingFactWidget*) it->second.second)->imageHeight;

    // Change the statement to something longer
    TestUtil::editCurrentFactStatement(window, longFactStatement);

    // Check the rendered image is not blank
    QVERIFY(factPage->statementImage->imageLoaded == true);

    // Check the size of the rendered images have increased
    QVERIFY(factPage->statementImage->image.height() > oldHeightOnFactPage);

    it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->imageHeight > oldHeightOnCoursePage);

    // Check that no part of the splitter is minimized
    auto sizes = factPage->splitter->sizes();
    QVERIFY(sizes.at(0) != 0);
    QVERIFY(sizes.at(1) != 0);
}

void FactTest::test_deleteFact_all()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Immediately delete the fact
    TestUtil::deleteCurrentFact(window);

    // Check that no facts are shown
    auto currentFactList = coursePage->factListView->currentFactList;
    QVERIFY(currentFactList->layout->count() == 0);
    QVERIFY(currentFactList->idChildMap.size() == 0);
    QVERIFY(currentFactList->idChildSectionMap.size() == 0);
    QVERIFY(currentFactList->idChildFactMap.size() == 0);
}

void FactTest::test_deleteFact_one()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *otherFactName = "The empty set is unique";
    const char *otherFactType = "Theorem";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";

    // Add our course and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, otherFactName, otherFactType);
    TestUtil::addFact(window, factName, factType);

    // Immediately delete the fact
    TestUtil::deleteCurrentFact(window);

    // Check that the course page shows one fact
    auto currentFactList = coursePage->factListView->currentFactList;
    QVERIFY(currentFactList->layout->count() == 1);
    QVERIFY(currentFactList->idChildMap.size() == 1);
    QVERIFY(currentFactList->idChildSectionMap.size() == 0);
    QVERIFY(currentFactList->idChildFactMap.size() == 1);

    // Check that the name is shown correctly on the course page
    auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    QVERIFY(((ExpandingFactWidget*) it->second.second)->fact.name == otherFactName);
}

void FactTest::test_factColours()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";

    const int numTypes = 7;
    const char *types[] = { "Definition", "Proposition", "Lemma", "Theorem", "Corollary", "Example", "Remark" };

    // Add our course
    TestUtil::addCourse(window, courseName);

    // Add all of our facts
    for (int i = 0; i < numTypes; i++) {
        TestUtil::addFact(window, types[i], types[i]);
    }

    // Check that each fact on the course page has the correct colour
    auto idChildMap = coursePage->factListView->currentFactList->idChildMap;
    for (auto it = idChildMap.begin(); it != idChildMap.end(); it++) {
        ExpandingFactWidget *factWidget = (ExpandingFactWidget*) it->second.second;

        QColor colour = QColor(QString::fromStdString(std::string("#") + findFactType(factWidget->nameLabel->text().toStdString()).colour));

        QVERIFY(QColor(factWidget->grab(QRect(40, 2, 1, 1)).toImage().pixel(0, 0)) == colour);
    }
}

void FactTest::test_viewFact_statementEmpty()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *otherFactName = "The empty set is unique";
    const char *otherFactType = "Theorem";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Leave the statement empty

    // add another fact
    TestUtil::addFact(window, otherFactName, otherFactType);

    // Select the first fact again
    ExpandingFactWidget* factWidget = (ExpandingFactWidget*) coursePage->factListView->currentFactList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == factName);
    QTest::mouseClick(factWidget->viewButton, Qt::LeftButton);

    // Check that the statement text edit and image are visible
    auto sizes = factPage->splitter->sizes();
    QVERIFY(sizes.at(0) != 0);
    QVERIFY(sizes.at(1) != 0);
}

void FactTest::test_viewFact_statementNotEmpty()
{
    CoursePage *coursePage = window->coursePage;
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *otherFactName = "The empty set is unique";
    const char *otherFactType = "Theorem";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";
    const char *factStatement = "Statement text!!!";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Change the statement to be non-empty
    TestUtil::editCurrentFactStatement(window, factStatement);

    // add another fact
    TestUtil::addFact(window, otherFactName, otherFactType);

    // Select the first fact again
    ExpandingFactWidget* factWidget = (ExpandingFactWidget*) coursePage->factListView->currentFactList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == factName);
    QTest::mouseClick(factWidget->viewButton, Qt::LeftButton);

    // Check that the statement text edit is not visible but the image is
    auto sizes = factPage->splitter->sizes();
    QVERIFY(sizes.at(0) == 0);
    QVERIFY(sizes.at(1) != 0);
}