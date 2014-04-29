#include "unistd.h"

#include <iostream>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
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
#include "forms/sectionForm.h"
#include "forms/proofForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/clickableQLabel.h"
#include "widgets/dialog.h"
#include "views/breadCrumbs.h"
#include "views/courseTitleWidget.h"
#include "views/factListView.h"
#include "views/factList.h"
#include "views/sectionPickerWidget.h"

#include "test/testUtil.h"



//   #####   #####  ##   ## ######   #####  #######
//  ##   ## ##   ## ##   ## ##   ## ##   ## ##
//  ##      ##   ## ##   ## ##   ##  ##     ##
//  ##      ##   ## ##   ## ##  ###   ###   #####
//  ##      ##   ## ##   ## #####       ##  ##
//  ##   ## ##   ## ##   ## ##  ##  ##   ## ##
//   #####   #####   #####  ##   ##  #####  #######

void TestUtil::addCourse(StudyAid *window, const char *name)
{
    RootPage *rootPage = window->rootPage;

    QTest::mouseClick(rootPage->newCourseButton, Qt::LeftButton);
    rootPage->courseAddForm->nameInput->setText(name);
    QTest::mouseClick(rootPage->courseAddDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::editCurrentCourse(StudyAid *window, const char *name)
{
    CoursePage *coursePage = window->coursePage;

    QTest::mouseClick(coursePage->editCourseButton, Qt::LeftButton);
    coursePage->courseEditForm->nameInput->setText(name);
    QTest::mouseClick(coursePage->courseEditDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::deleteCurrentCourse(StudyAid *window)
{
    CoursePage *coursePage = window->coursePage;

    QTest::mouseClick(coursePage->deleteCourseButton, Qt::LeftButton);
    QTest::mouseClick(coursePage->courseDeleteDialog->confirmButton, Qt::LeftButton);
}



//  #######    ##     #####  ########
//  ##        ####   ##   ##    ##
//  ##       ##  ##  ##         ##
//  #####   ##    ## ##         ##
//  ##      ######## ##         ##
//  ##      ##    ## ##   ##    ##
//  ##      ##    ##  #####     ##

void TestUtil::addFact(StudyAid *window, const char *name, const char *type)
{
    CoursePage *coursePage = window->coursePage;

    QTest::mouseClick(coursePage->factListView->currentFactList->addFactButton, Qt::LeftButton);

    coursePage->factListView->factAddForm->nameInput->setText(name);

    auto typeInput = coursePage->factListView->factAddForm->typeInput;
    typeInput->setCurrentIndex(typeInput->findText(type));

    QTest::mouseClick(coursePage->factListView->factAddDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::editCurrentFact(StudyAid *window, const char *name, const char *type)
{
    FactPage *factPage = window->factPage;

    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);

    factPage->factEditForm->nameInput->setText(name);

    auto typeInput = factPage->factEditForm->typeInput;
    typeInput->setCurrentIndex(typeInput->findText(type));

    QTest::mouseClick(factPage->factEditDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::editCurrentFactStatement(StudyAid *window, const char *statement)
{
    FactPage *factPage = window->factPage;

    factPage->statementTextEdit->setPlainText(statement);
    factPage->saveStatement();
}

void TestUtil::deleteCurrentFact(StudyAid *window)
{
    FactPage *factPage = window->factPage;

    QTest::mouseClick(factPage->deleteFactButton, Qt::LeftButton);
    QTest::mouseClick(factPage->factDeleteDialog->confirmButton, Qt::LeftButton);
}



//  ######  ######   #####   #####  #######
//  ##   ## ##   ## ##   ## ##   ## ##
//  ##   ## ##   ## ##   ## ##   ## ##
//  ######  ######  ##   ## ##   ## #####
//  ##      ##  ##  ##   ## ##   ## ##
//  ##      ##   ## ##   ## ##   ## ##
//  ##      ##    #  #####   #####  ##

void TestUtil::addProof(StudyAid *window, const char *name)
{
    FactPage *factPage = window->factPage;

    QTest::mouseClick(factPage->addProofButton, Qt::LeftButton);

    factPage->proofAddForm->nameInput->setText(name);

    QTest::mouseClick(factPage->proofAddDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::editCurrentProof(StudyAid *window, const char *name)
{
    ProofPage *proofPage = window->proofPage;

    QTest::mouseClick(proofPage->editProofButton, Qt::LeftButton);

    proofPage->proofEditForm->nameInput->setText(name);

    QTest::mouseClick(proofPage->proofEditDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::editCurrentProofBody(StudyAid *window, const char *body)
{
    ProofPage *proofPage = window->proofPage;

    proofPage->bodyTextEdit->setPlainText(body);
    proofPage->saveBody();
}

void TestUtil::deleteCurrentProof(StudyAid *window)
{
    ProofPage *proofPage = window->proofPage;

    QTest::mouseClick(proofPage->deleteProofButton, Qt::LeftButton);
    QTest::mouseClick(proofPage->proofDeleteDialog->confirmButton, Qt::LeftButton);
}



//   #####  ######  #####  ######## ####  #####  ##    ##
//  ##   ## ##     ##   ##    ##     ##  ##   ## ###   ##
//   ##     ##     ##         ##     ##  ##   ## ####  ##
//    ###   ####   ##         ##     ##  ##   ## ## ## ##
//      ##  ##     ##         ##     ##  ##   ## ##  ####
//  ##   ## ##     ##   ##    ##     ##  ##   ## ##   ###
//   #####  ######  #####     ##    ####  #####  ##    ##

void TestUtil::addFactToSection(StudyAid *window, const char *factName, const char *factType, const char *sectionName)
{
    FactList *factList = findFactList(window, sectionName, window->coursePage->factListView->currentFactList);

    if (factList == nullptr) {
        return;
    }

    QTest::mouseClick(factList->addFactButton, Qt::LeftButton);

    factList->factAddForm->nameInput->setText(factName);

    auto typeInput = factList->factAddForm->typeInput;
    typeInput->setCurrentIndex(typeInput->findText(factType));

    QTest::mouseClick(factList->factAddDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::editSection(StudyAid *window, const char *newSectionName, const char *oldSectionName)
{
    FactList *factList = findFactList(window, oldSectionName, window->coursePage->factListView->currentFactList);

    if (factList == nullptr) {
        return;
    }

    QTest::mouseClick(factList->editSectionButton, Qt::LeftButton);

    factList->sectionEditForm->nameInput->setText(newSectionName);

    QTest::mouseClick(factList->sectionEditDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::deleteSection(StudyAid *window, const char *sectionName)
{
    FactList *factList = findFactList(window, sectionName, window->coursePage->factListView->currentFactList);

    if (factList == nullptr) {
        return;
    }

    QTest::mouseClick(factList->deleteSectionButton, Qt::LeftButton);
    QTest::mouseClick(factList->sectionDeleteDialog->confirmButton, Qt::LeftButton);
}

void TestUtil::selectSection(StudyAid *window, const char *sectionName)
{
    SectionPickerWidget *sectionPicker = findSectionPicker(window, sectionName, window->coursePage->sectionPicker);

    if (sectionPicker == nullptr) {
        return;
    }

    QTest::mouseClick(sectionPicker->sectionLabel, Qt::LeftButton);
}

FactList *TestUtil::findFactList(StudyAid *window, const char *name, FactList *searchRoot)
{
    if (searchRoot->sectionNameLabel->text() == name) {
        return searchRoot;
    }

    for (auto it = searchRoot->idChildSectionMap.begin(); it != searchRoot->idChildSectionMap.end(); it++) {
        auto picker = findFactList(window, name, it->second);
        if (picker != nullptr) {
            return picker;
        }
    }

    return nullptr;
}

SectionPickerWidget *TestUtil::findSectionPicker(StudyAid *window, const char *name, SectionPickerWidget *searchRoot)
{
    if (searchRoot->sectionLabel->text() == name) {
        return searchRoot;
    }

    for (auto it = searchRoot->idSectionPickerMap.begin(); it != searchRoot->idSectionPickerMap.end(); it++) {
        auto picker = findSectionPicker(window, name, it->second);
        if (picker != nullptr) {
            return picker;
        }
    }

    return nullptr;
}