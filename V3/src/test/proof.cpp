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
#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "pages/proofPage.h"
#include "forms/courseForm.h"
#include "forms/factForm.h"
#include "forms/proofForm.h"
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
#include "views/proofViewWidget.h"

#include "test/testUtil.h"

#include "test/proof.h"

void ProofTest::init()
{
    clearTestDatabase();

    window = new StudyAid();
}

void ProofTest::cleanup()
{
    delete window;
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
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second.second->nameLabel->text() == proofName);
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
    QVERIFY(it->second.second->nameLabel->text() == otherProofName);

    it++;
    QVERIFY(it->second.second->nameLabel->text() == proofName);
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
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second.second->nameLabel->text() == newProofName);
}

void ProofTest::test_editProof_body()
{
    FactPage *factPage = window->factPage;
    ProofPage *proofPage = window->proofPage;

    const char *courseName = "Set Theory";
    const char *factName = "The empty set is unique";
    const char *factType = "Theorem";
    const char *proofName = "Direct proof";
    const char *shortProofBody = "Single line";
    const char *longProofBody = "Multiple\\\\\n... lines!";

    // Add our course and fact and proof
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, factName, factType);
    TestUtil::addProof(window, proofName);

    // Check the body is empty
    QVERIFY(proofPage->bodyTextEdit->toPlainText() == "");
    QVERIFY(proofPage->bodyImage->imageLoaded == false);

    // Change the body to something short but nonempty
    TestUtil::editCurrentProofBody(window, shortProofBody);

    // Check the rendered image is not blank
    QVERIFY(proofPage->bodyImage->imageLoaded == true);

    // Record the size of the images
    int oldHeightOnProofPage = proofPage->bodyImage->image.height();
    int oldHeightOnFactPage = factPage->idProofViewWidgetMap.begin()->second.second->bodyImage->image.height();

    // Change the body to something longer
    TestUtil::editCurrentProofBody(window, longProofBody);

    // Check the rendered image is not blank
    QVERIFY(proofPage->bodyImage->imageLoaded == true);

    // Check the size of the rendered images have increased
    QVERIFY(proofPage->bodyImage->image.height() > oldHeightOnProofPage);
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second.second->bodyImage->image.height() > oldHeightOnFactPage);
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
    QVERIFY(factPage->idProofViewWidgetMap.begin()->second.second->nameLabel->text() == otherProofName);
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
    ProofViewWidget *proofViewWidget = factPage->idProofViewWidgetMap.begin()->second.second;
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
    ProofViewWidget *proofViewWidget = factPage->idProofViewWidgetMap.begin()->second.second;
    QVERIFY(proofViewWidget->nameLabel->text() == proofName);
    QTest::mouseClick(proofViewWidget->viewProofButton, Qt::LeftButton);

    // Check that the body text edit is not visible but the image is
    auto sizes = proofPage->splitter->sizes();
    QVERIFY(sizes.at(0) == 0);
    QVERIFY(sizes.at(1) != 0);
}