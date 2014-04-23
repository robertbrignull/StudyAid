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
#include "model.h"
#include "database/setup.h"
#include "database/methods.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
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
#include "views/sectionPickerWidget.h"

#include "test/testUtil.h"

#include "test/fact.h"

void FactTest::init()
{
    clearTestDatabase();

    modelSignaller = new ModelSignaller();
    window = new StudyAid(modelSignaller);
}

void FactTest::cleanup()
{
    delete window;
    delete modelSignaller;
}

void FactTest::test_addFact_form()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";

    // Add our course
    TestUtil::addCourse(window, courseName);

    // Open the dialog
    QTest::mouseClick(coursePage->sectionPicker->addFactButton, Qt::LeftButton);

    // Check that the dialog is showing
    QVERIFY(coursePage->factAddDialog->isHidden() == false);

    // Check that the accept button is disabled
    QVERIFY(coursePage->factAddDialog->confirmButton->isEnabled() == false);

    // Change the name to be non-empty
    coursePage->factAddForm->nameInput->setText(courseName);

    // Check that the accept button is enabled
    QVERIFY(coursePage->factAddDialog->confirmButton->isEnabled() == true);

    // Change the name to be empty
    coursePage->factAddForm->nameInput->setText("");

    // Check that the accept button is disabled
    QVERIFY(coursePage->factAddDialog->confirmButton->isEnabled() == false);

    // Close the dialog
    QTest::mouseClick(coursePage->factAddDialog->cancelButton, Qt::LeftButton);

    // Check that the dialog closed
    QVERIFY(coursePage->factAddDialog->isHidden() == true);
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

void FactTest::test_editFact_form()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Open the dialog
    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);

    // Check that the dialog is showing
    QVERIFY(factPage->factEditDialog->isHidden() == false);

    // Check that the accept button is enabled
    QVERIFY(factPage->factEditDialog->confirmButton->isEnabled() == true);

    // Change the name to be empty
    factPage->factEditForm->nameInput->setText("");

    // Check that the accept button is disabled
    QVERIFY(factPage->factEditDialog->confirmButton->isEnabled() == false);

    // Change the name to be non-empty
    factPage->factEditForm->nameInput->setText(courseName);

    // Check that the accept button is disabled
    QVERIFY(factPage->factEditDialog->confirmButton->isEnabled() == true);

    // Close the dialog
    QTest::mouseClick(factPage->factEditDialog->cancelButton, Qt::LeftButton);

    // Check that the dialog closed
    QVERIFY(factPage->factEditDialog->isHidden() == true);
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
    // CoursePage *coursePage = window->coursePage;
    // FactPage *factPage = window->factPage;

    // const char *courseName = "Set Theory";
    // const char *factName = "ZF1 - Extensionality";
    // const char *factType = "Axiom";
    // const char *shortFactStatement = "Single line";
    // const char *longFactStatement = "Multiple\\\\\n... lines!";

    // // Add our course and fact
    // TestUtil::addCourse(window, courseName);
    // TestUtil::addFact(window, factName, factType);

    // // Check the statement is empty
    // QVERIFY(factPage->statementTextEdit->toPlainText() == "");
    // QVERIFY(factPage->statementImage->imageLoaded == false);

    // // Change the statement to something short but nonempty
    // TestUtil::editCurrentFactStatement(window, shortFactStatement);

    // // Wait for it to render
    // QTest::qWait(1000);

    // // Check the rendered image is not blank
    // QVERIFY(factPage->statementImage->imageLoaded == true);

    // // Record the size of the image
    // int oldHeightOnFactPage = factPage->statementImage->image.height();

    // auto it = coursePage->factListView->currentFactList->idChildMap.begin();
    // int oldHeightOnCoursePage = ((ExpandingFactWidget*) it->second.second)->imageHeight;

    // // Change the statement to something longer
    // TestUtil::editCurrentFactStatement(window, longFactStatement);

    // // Wait for it to render
    // QTest::qWait(1000);

    // // Check the rendered image is not blank
    // QVERIFY(factPage->statementImage->imageLoaded == true);

    // // Check the size of the rendered images have increased
    // QVERIFY(factPage->statementImage->image.height() > oldHeightOnFactPage);

    // it = coursePage->factListView->currentFactList->idChildMap.begin();
    // QVERIFY(((ExpandingFactWidget*) it->second.second)->imageHeight > oldHeightOnCoursePage);

    // // Check that no part of the splitter is minimized
    // auto sizes = factPage->splitter->sizes();
    // QVERIFY(sizes.at(0) != 0);
    // QVERIFY(sizes.at(1) != 0);
}

void FactTest::test_editFactOrdering_moveMode()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName1 = "ZF1 - Extensionality";
    const char *factType1 = "Axiom";
    const char *factName2 = "The empty set is unique";
    const char *factType2 = "Theorem";

    // Add the course, fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName1, factType1);
    TestUtil::addFact(window, factName2, factType2);

    // Check that the correct buttons are visible
    auto it = coursePage->factListView->currentFactList->idChildFactMap.begin();
    auto factWidget1 = it->second;
    it++;
    auto factWidget2 = it->second;

    QVERIFY(factWidget1->moveButton->isHidden() == false);
    QVERIFY(factWidget1->viewButton->isHidden() == false);
    QVERIFY(factWidget1->moveAboveButton->isHidden() == true);
    QVERIFY(factWidget1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(factWidget2->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(factWidget1->moveButton->isHidden() == true);
    QVERIFY(factWidget1->viewButton->isHidden() == true);
    QVERIFY(factWidget1->moveAboveButton->isHidden() == false);
    QVERIFY(factWidget1->moveBelowButton->isHidden() == false);

    // Click the moveAboveButton
    QTest::mouseClick(factWidget2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(factWidget1->moveButton->isHidden() == false);
    QVERIFY(factWidget1->viewButton->isHidden() == false);
    QVERIFY(factWidget1->moveAboveButton->isHidden() == true);
    QVERIFY(factWidget1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(factWidget2->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(factWidget1->moveButton->isHidden() == true);
    QVERIFY(factWidget1->viewButton->isHidden() == true);
    QVERIFY(factWidget1->moveAboveButton->isHidden() == false);
    QVERIFY(factWidget1->moveBelowButton->isHidden() == false);

    // Click the moveBelowButton
    QTest::mouseClick(factWidget2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(factWidget1->moveButton->isHidden() == false);
    QVERIFY(factWidget1->viewButton->isHidden() == false);
    QVERIFY(factWidget1->moveAboveButton->isHidden() == true);
    QVERIFY(factWidget1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(factWidget2->moveButton, Qt::LeftButton);

    // Check that only the move button is visible
    QVERIFY(factWidget2->moveButton->isHidden() == false);
    QVERIFY(factWidget2->viewButton->isHidden() == true);
    QVERIFY(factWidget2->moveAboveButton->isHidden() == true);
    QVERIFY(factWidget2->moveBelowButton->isHidden() == true);

    // Click the move cancel button
    QTest::mouseClick(factWidget2->moveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(factWidget2->moveButton->isHidden() == false);
    QVERIFY(factWidget2->viewButton->isHidden() == false);
    QVERIFY(factWidget2->moveAboveButton->isHidden() == true);
    QVERIFY(factWidget2->moveBelowButton->isHidden() == true);
}

void FactTest::test_editFactOrdering_moveAbove()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName1 = "ZF1 - Extensionality";
    const char *factType1 = "Axiom";
    const char *factName2 = "The empty set is unique";
    const char *factType2 = "Theorem";

    // Add the course and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName1, factType1);
    TestUtil::addFact(window, factName2, factType2);

    // Move the second proof above the first
    auto currentFactListLayout = coursePage->factListView->currentFactList->layout;
    QTest::mouseClick(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->moveAboveButton, Qt::LeftButton);

    // Check that the proofs are now in the correct order
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->fact.name == factName2);
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.name == factName1);

    // Check that the orderings are valid
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->fact.ordering < ((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.ordering);
}

void FactTest::test_editFactOrdering_moveBelow()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName1 = "ZF1 - Extensionality";
    const char *factType1 = "Axiom";
    const char *factName2 = "The empty set is unique";
    const char *factType2 = "Theorem";

    // Add our course, fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName1, factType1);
    TestUtil::addFact(window, factName2, factType2);

    // Move the first proof below the second
    auto currentFactListLayout = coursePage->factListView->currentFactList->layout;
    QTest::mouseClick(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the proofs are now in the correct order
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->fact.name == factName2);
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.name == factName1);

    // Check that the orderings are valid
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->fact.ordering < ((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.ordering);
}

void FactTest::test_editFactOrdering_moveBetween()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName1 = "ZF1 - Extensionality";
    const char *factType1 = "Axiom";
    const char *factName2 = "ZF2 - Empty Set";
    const char *factType2 = "Axiom";
    const char *factName3 = "The empty set is unique";
    const char *factType3 = "Theorem";

    // Add our course, fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName1, factType1);
    TestUtil::addFact(window, factName2, factType2);
    TestUtil::addFact(window, factName3, factType3);

    // Move the first proof below the second
    auto currentFactListLayout = coursePage->factListView->currentFactList->layout;
    QTest::mouseClick(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the proofs are now in the correct order
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->fact.name == factName2);
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.name == factName1);
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(2)->widget())->fact.name == factName3);

    // Check that the orderings are valid
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(0)->widget())->fact.ordering < ((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.ordering);
    QVERIFY(((ExpandingFactWidget*) currentFactListLayout->itemAt(1)->widget())->fact.ordering < ((ExpandingFactWidget*) currentFactListLayout->itemAt(2)->widget())->fact.ordering);
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