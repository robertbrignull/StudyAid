#include <iostream>
#include <map>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>
#include <QTextEdit>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "model.h"
#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "pages/proofPage.h"
#include "forms/proofForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"
#include "widgets/dialog.h"
#include "widgets/splitter.h"
#include "views/breadCrumbs.h"
#include "views/proofViewWidget.h"
#include "views/factListView.h"
#include "views/factList.h"
#include "views/expandingFactWidget.h"
#include "views/proofViewWidget.h"

#include "test/testUtil.h"

#include "test/proof.h"

void ProofTest::init()
{
    clearTestDatabase();

    modelSignaller = new ModelSignaller();
    window = new StudyAid(modelSignaller);
}

void ProofTest::cleanup()
{
    delete window;
    delete modelSignaller;
}

void ProofTest::test_addProof_form()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Open the dialog
    QTest::mouseClick(factPage->addProofButton, Qt::LeftButton);

    // Check that the dialog is showing
    QVERIFY(factPage->proofAddDialog->isHidden() == false);

    // Check that the accept button is enabled
    QVERIFY(factPage->proofAddDialog->confirmButton->isEnabled() == true);

    // Change the name to be non-empty
    factPage->proofAddForm->nameInput->setText(proofName);

    // Check that the accept button is still enabled
    QVERIFY(factPage->proofAddDialog->confirmButton->isEnabled() == true);

    // Change the name to be empty
    factPage->proofAddForm->nameInput->setText("");

    // Check that the accept button is still enabled
    QVERIFY(factPage->proofAddDialog->confirmButton->isEnabled() == true);

    // Close the dialog
    QTest::mouseClick(factPage->proofAddDialog->cancelButton, Qt::LeftButton);

    // Check that the dialog closed
    QVERIFY(factPage->proofAddDialog->isHidden() == true);
}

void ProofTest::test_addProof()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Check that no proofs are shown
    QVERIFY(factPage->idProofViewWidgetMap.size() == 0);
    QVERIFY(factPage->proofsScrollLayout->count() == 1);

    // Add our proof
    TestUtil::addProof(window, proofName);

    // Check that we're on the proof page
    QVERIFY(window->stack->currentIndex() == 3);

    // Check that the name is shown correctly on the proof page
    QVERIFY(proofPage->proofLabel->text() == proofName);
    QVERIFY(proofPage->breadCrumbs->currentProofLabel->text() == proofName);

    // Check that the name is correct in the editProofDialog
    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);
    QVERIFY(proofPage->proofEditForm->nameInput->text() == proofName);
    QTest::mouseClick(proofPage->proofEditDialog->cancelButton, Qt::LeftButton);

    // Check that the fact page shows one proof
    QVERIFY(factPage->idProofViewWidgetMap.size() == 1);
    QVERIFY(factPage->proofsScrollLayout->count() == 2);

    // Check that the name is correct on the fact page
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second->nameLabel->text() == proofName);
}

void ProofTest::test_addProof_multiple()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *otherProofName = "Some other proof";
    const char *proofName = "Direct proof";

    // Add our course and fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, otherProofName);
    TestUtil::addProof(window, proofName);

    // Check that the name is shown correctly on the proof page
    QVERIFY(proofPage->proofLabel->text() == proofName);
    QVERIFY(proofPage->breadCrumbs->currentProofLabel->text() == proofName);

    // Check that the name is correct in the editProofDialog
    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);
    QVERIFY(proofPage->proofEditForm->nameInput->text() == proofName);
    QTest::mouseClick(proofPage->proofEditDialog->cancelButton, Qt::LeftButton);

    // Check that the fact page shows two proofs
    QVERIFY(factPage->idProofViewWidgetMap.size() == 2);
    QVERIFY(factPage->proofsScrollLayout->count() == 3);

    // Check that the name is correct on the fact page
    auto it = factPage->idProofViewWidgetMap.begin();
    QVERIFY(it->second->nameLabel->text() == otherProofName);

    it++;
    QVERIFY(it->second->nameLabel->text() == proofName);
}

void ProofTest::test_addProof_nameEmpty()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "";
    const char *visibleProofName = "Proof";

    // Add our course and fact
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);

    // Add our proof
    TestUtil::addProof(window, proofName);

    // Check that the name is shown correctly on the proof page
    QVERIFY(proofPage->proofLabel->text() == visibleProofName);
    QVERIFY(proofPage->breadCrumbs->currentProofLabel->text() == visibleProofName);

    // Check that the name is correct in the editProofDialog
    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);
    QVERIFY(proofPage->proofEditForm->nameInput->text() == proofName);
    QTest::mouseClick(proofPage->proofEditDialog->cancelButton, Qt::LeftButton);

    // Check that the name is correct on the fact page
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second->nameLabel->text() == visibleProofName);
}

void ProofTest::test_editProof_form()
{
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";

    // Add our course and fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Open the dialog
    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);

    // Check that the dialog is showing
    QVERIFY(proofPage->proofEditDialog->isHidden() == false);

    // Check that the accept button is enabled
    QVERIFY(proofPage->proofEditDialog->confirmButton->isEnabled() == true);

    // Change the name to be empty
    proofPage->proofEditForm->nameInput->setText("");

    // Check that the accept button is still enabled
    QVERIFY(proofPage->proofEditDialog->confirmButton->isEnabled() == true);

    // Change the name to be non-empty
    proofPage->proofEditForm->nameInput->setText(proofName);

    // Check that the accept button is still enabled
    QVERIFY(proofPage->proofEditDialog->confirmButton->isEnabled() == true);

    // Close the dialog
    QTest::mouseClick(proofPage->proofEditDialog->cancelButton, Qt::LeftButton);

    // Check that the dialog closed
    QVERIFY(proofPage->proofEditDialog->isHidden() == true);
}

void ProofTest::test_editProof()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";
    const char *newProofName = "Some other proof";

    // Add our course and fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Immeditately change the name of the proof
    TestUtil::editCurrentProof(window, newProofName);

    // Check that the name is shown correctly on the proof page
    QVERIFY(proofPage->proofLabel->text() == newProofName);
    QVERIFY(proofPage->breadCrumbs->currentProofLabel->text() == newProofName);

    // Check that the name is correct in the editProofDialog
    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);
    QVERIFY(proofPage->proofEditForm->nameInput->text() == newProofName);
    QTest::mouseClick(proofPage->proofEditDialog->cancelButton, Qt::LeftButton);

    // Check that the fact page shows one proof
    QVERIFY(factPage->idProofViewWidgetMap.size() == 1);
    QVERIFY(factPage->proofsScrollLayout->count() == 2);

    // Check that the name is correct on the fact page
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second->nameLabel->text() == newProofName);
}

void ProofTest::test_editProof_body()
{
    // FactPage *factPage = window->factPage;
    // ProofPage *proofPage = window->proofPage;

    // const char *courseName = "Set Theory";
    // const char *factName = "The empty set is unique";
    // const char *factType = "Theorem";
    // const char *proofName = "Direct proof";
    // const char *shortProofBody = "Single line";
    // const char *longProofBody = "Multiple\\\\\n... lines!";

    // // Add our course and fact and proof
    // TestUtil::addCourse(window, courseName);
    // TestUtil::addFact(window, factName, factType);
    // TestUtil::addProof(window, proofName);

    // // Check the body is empty
    // QVERIFY(proofPage->bodyTextEdit->toPlainText() == "");
    // QVERIFY(proofPage->bodyImage->imageLoaded == false);

    // // Change the body to something short but nonempty
    // TestUtil::editCurrentProofBody(window, shortProofBody);

    // // Wait for it to render
    // QTest::qWait(1000);

    // // Check the rendered image is not blank
    // QVERIFY(proofPage->bodyImage->imageLoaded == true);

    // // Record the size of the images
    // int oldHeightOnProofPage = proofPage->bodyImage->image.height();
    // int oldHeightOnFactPage = factPage->idProofViewWidgetMap.begin()->second->bodyImage->image.height();

    // // Change the body to something longer
    // TestUtil::editCurrentProofBody(window, longProofBody);

    // // Wait for it to render
    // QTest::qWait(1000);

    // // Check the rendered image is not blank
    // QVERIFY(proofPage->bodyImage->imageLoaded == true);

    // // Check the size of the rendered images have increased
    // QVERIFY(proofPage->bodyImage->image.height() > oldHeightOnProofPage);
    // QVERIFY(factPage->idProofViewWidgetMap.begin()->second->bodyImage->image.height() > oldHeightOnFactPage);
}

void ProofTest::test_editProof_nameEmpty()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";
    const char *newProofName = "";
    const char *newVisibleProofName = "Proof";

    // Add our course and fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Immeditately change the name of the proof
    TestUtil::editCurrentProof(window, newProofName);

    // Check that the name is shown correctly on the proof page
    QVERIFY(proofPage->proofLabel->text() == newVisibleProofName);
    QVERIFY(proofPage->breadCrumbs->currentProofLabel->text() == newVisibleProofName);

    // Check that the name is correct in the editProofDialog
    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);
    QVERIFY(proofPage->proofEditForm->nameInput->text() == newProofName);
    QTest::mouseClick(proofPage->proofEditDialog->cancelButton, Qt::LeftButton);

    // Check that the name is correct on the fact page
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second->nameLabel->text() == newVisibleProofName);
}

void ProofTest::test_editProofOrdering_moveMode()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName1 = "Direct proof";
    const char *proofName2 = "Other proof type";

    // Add the course, fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName1);
    TestUtil::addProof(window, proofName2);

    // Check that the correct buttons are visible
    auto it = factPage->idProofViewWidgetMap.begin();
    auto proofViewWidget1 = it->second;
    it++;
    auto proofViewWidget2 = it->second;

    QVERIFY(proofViewWidget1->moveButton->isHidden() == false);
    QVERIFY(proofViewWidget1->viewProofButton->isHidden() == false);
    QVERIFY(proofViewWidget1->moveAboveButton->isHidden() == true);
    QVERIFY(proofViewWidget1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(proofViewWidget2->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(proofViewWidget1->moveButton->isHidden() == true);
    QVERIFY(proofViewWidget1->viewProofButton->isHidden() == true);
    QVERIFY(proofViewWidget1->moveAboveButton->isHidden() == false);
    QVERIFY(proofViewWidget1->moveBelowButton->isHidden() == false);

    // Click the moveAboveButton
    QTest::mouseClick(proofViewWidget2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(proofViewWidget1->moveButton->isHidden() == false);
    QVERIFY(proofViewWidget1->viewProofButton->isHidden() == false);
    QVERIFY(proofViewWidget1->moveAboveButton->isHidden() == true);
    QVERIFY(proofViewWidget1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(proofViewWidget2->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(proofViewWidget1->moveButton->isHidden() == true);
    QVERIFY(proofViewWidget1->viewProofButton->isHidden() == true);
    QVERIFY(proofViewWidget1->moveAboveButton->isHidden() == false);
    QVERIFY(proofViewWidget1->moveBelowButton->isHidden() == false);

    // Click the moveBelowButton
    QTest::mouseClick(proofViewWidget2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(proofViewWidget1->moveButton->isHidden() == false);
    QVERIFY(proofViewWidget1->viewProofButton->isHidden() == false);
    QVERIFY(proofViewWidget1->moveAboveButton->isHidden() == true);
    QVERIFY(proofViewWidget1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(proofViewWidget2->moveButton, Qt::LeftButton);

    // Check that only the move button is visible
    QVERIFY(proofViewWidget2->moveButton->isHidden() == false);
    QVERIFY(proofViewWidget2->viewProofButton->isHidden() == true);
    QVERIFY(proofViewWidget2->moveAboveButton->isHidden() == true);
    QVERIFY(proofViewWidget2->moveBelowButton->isHidden() == true);

    // Click the move cancel button
    QTest::mouseClick(proofViewWidget2->moveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(proofViewWidget2->moveButton->isHidden() == false);
    QVERIFY(proofViewWidget2->viewProofButton->isHidden() == false);
    QVERIFY(proofViewWidget2->moveAboveButton->isHidden() == true);
    QVERIFY(proofViewWidget2->moveBelowButton->isHidden() == true);
}

void ProofTest::test_editProofOrdering_moveAbove()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName1 = "Proof 1";
    const char *proofName2 = "Proof 2";

    // Add the course, fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName1);
    TestUtil::addProof(window, proofName2);

    // Move the second proof above the first
    QTest::mouseClick(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->moveAboveButton, Qt::LeftButton);

    // Check that the proofs are now in the correct order
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->proof.name == proofName2);
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.name == proofName1);

    // Check that the orderings are valid
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->proof.ordering < ((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.ordering);
}

void ProofTest::test_editProofOrdering_moveBelow()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName1 = "Proof 1";
    const char *proofName2 = "Proof 2";

    // Add our course, fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName1);
    TestUtil::addProof(window, proofName2);

    // Move the first proof below the second
    QTest::mouseClick(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the proofs are now in the correct order
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->proof.name == proofName2);
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.name == proofName1);

    // Check that the orderings are valid
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->proof.ordering < ((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.ordering);
}

void ProofTest::test_editProofOrdering_moveBetween()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName1 = "Proof 1";
    const char *proofName2 = "Proof 2";
    const char *proofName3 = "Proof 3";

    // Add our course, fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName1);
    TestUtil::addProof(window, proofName2);
    TestUtil::addProof(window, proofName3);

    // Move the first proof below the second
    QTest::mouseClick(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the proofs are now in the correct order
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->proof.name == proofName2);
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.name == proofName1);
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(2)->widget())->proof.name == proofName3);

    // Check that the orderings are valid
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(0)->widget())->proof.ordering < ((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.ordering);
    QVERIFY(((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(1)->widget())->proof.ordering < ((ProofViewWidget*) factPage->proofsScrollLayout->itemAt(2)->widget())->proof.ordering);
}

void ProofTest::test_deleteProof_all()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";

    // Add our course and fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Immediately delete the proof
    TestUtil::deleteCurrentProof(window);

    // Check that we're on the fact page
    QVERIFY(window->stack->currentIndex() == 2);

    // Check that the fact page shows no proofs
    QVERIFY(factPage->idProofViewWidgetMap.size() == 0);
    QVERIFY(factPage->proofsScrollLayout->count() == 1);
}

void ProofTest::test_deleteProof_one()
{
    FactPage *factPage = window->factPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *otherProofName = "Some other proof";
    const char *proofName = "Direct proof";

    // Add our course and fact and proofs
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, otherProofName);
    TestUtil::addProof(window, proofName);

    // Immediately delete the proof
    TestUtil::deleteCurrentProof(window);

    // Check that we're on the fact page
    QVERIFY(window->stack->currentIndex() == 2);

    // Check that the fact page shows one proof
    QVERIFY(factPage->idProofViewWidgetMap.size() == 1);
    QVERIFY(factPage->proofsScrollLayout->count() == 2);

    // Check that the name is correct on the fact page
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second->nameLabel->text() == otherProofName);
}

void ProofTest::test_viewProof_bodyEmpty()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";
    const char *proofName = "Proof 1";
    const char *otherProofName = "Proof 2";

    // Add our course and fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Leave the body empty

    // add another proof
    TestUtil::addProof(window, otherProofName);

    // Select the first proof again
    ProofViewWidget *proofViewWidget = factPage->idProofViewWidgetMap.begin()->second;
    QVERIFY(proofViewWidget->nameLabel->text() == proofName);
    QTest::mouseClick(proofViewWidget->viewProofButton, Qt::LeftButton);

    // Check that the body text edit and image are visible
    auto sizes = proofPage->splitter->sizes();
    QVERIFY(sizes.at(0) != 0);
    QVERIFY(sizes.at(1) != 0);
}

void ProofTest::test_viewProof_bodyNotEmpty()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "ZF1 - Extensionality";
    const char *factType = "Axiom";
    const char *proofName = "Proof 1";
    const char *otherProofName = "Proof 2";
    const char *proofBody = "Proof body text!!!";

    // Add our course and fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Change the body to something non-empty
    TestUtil::editCurrentProofBody(window, proofBody);

    // add another proof
    TestUtil::addProof(window, otherProofName);

    // Select the first proof again
    ProofViewWidget *proofViewWidget = factPage->idProofViewWidgetMap.begin()->second;
    QVERIFY(proofViewWidget->nameLabel->text() == proofName);
    QTest::mouseClick(proofViewWidget->viewProofButton, Qt::LeftButton);

    // Check that the body text edit is not visible but the image is
    auto sizes = proofPage->splitter->sizes();
    QVERIFY(sizes.at(0) == 0);
    QVERIFY(sizes.at(1) != 0);
}