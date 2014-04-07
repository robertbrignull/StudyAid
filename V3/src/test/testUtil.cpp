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
#include "widgets/sectionPickerWidget.h"

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
    QTest::mouseClick(rootPage->courseAddDialog->completeButton, Qt::LeftButton);
}

void TestUtil::editCurrentCourse(StudyAid *window, const char *name)
{
    CoursePage *coursePage = window->coursePage;

    QTest::mouseClick(coursePage->editCourseButton, Qt::LeftButton);
    coursePage->courseEditForm->nameInput->setText(name);
    QTest::mouseClick(coursePage->courseEditDialog->completeButton, Qt::LeftButton);
}

void TestUtil::deleteCurrentCourse(StudyAid *window)
{
    CoursePage *coursePage = window->coursePage;

    QTest::mouseClick(coursePage->deleteCourseButton, Qt::LeftButton);
    QTest::mouseClick(coursePage->courseDeleteDialog->acceptButton, Qt::LeftButton);
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

    QTest::mouseClick(coursePage->sectionPicker->addFactButton, Qt::LeftButton);

    coursePage->sectionPicker->factAddForm->nameInput->setText(name);

    auto typeInput = coursePage->sectionPicker->factAddForm->typeInput;
    typeInput->setCurrentIndex(typeInput->findText(type));

    QTest::mouseClick(coursePage->sectionPicker->factAddDialog->completeButton, Qt::LeftButton);
}

void TestUtil::editCurrentFact(StudyAid *window, const char *name, const char *type)
{
    FactPage *factPage = window->factPage;

    QTest::mouseClick(factPage->editFactButton, Qt::LeftButton);

    factPage->factEditForm->nameInput->setText(name);

    auto typeInput = factPage->factEditForm->typeInput;
    typeInput->setCurrentIndex(typeInput->findText(type));

    QTest::mouseClick(factPage->factEditDialog->completeButton, Qt::LeftButton);
}

void TestUtil::editCurrentFactStatement(StudyAid *window, const char *statement)
{
    window->factPage->statementTextEdit->setPlainText(statement);
    window->factPage->saveStatement();
}

void TestUtil::deleteCurrentFact(StudyAid *window)
{
    FactPage *factPage = window->factPage;

    QTest::mouseClick(factPage->deleteFactButton, Qt::LeftButton);
    QTest::mouseClick(factPage->factDeleteDialog->acceptButton, Qt::LeftButton);
}