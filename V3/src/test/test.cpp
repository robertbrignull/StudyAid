#include "unistd.h"

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
#include "dialogs/formDialog.h"
#include "forms/courseForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/breadCrumbs.h"
#include "widgets/courseTitleWidget.h"
#include "widgets/factListView.h"
#include "widgets/factList.h"

#include "test/test.h"

void Test::init()
{
    clearTestDatabase();

    window = new StudyAid();
    window->setWindowTitle("StudyAid");
    window->show(); 
}

void Test::cleanup()
{
    delete window;
}

void Test::test_addCourse()
{
    const char* newCourseName = "Set Theory";

    QVERIFY(window->stack->currentIndex() == 0);

    RootPage *rootPage = window->rootPage;

    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);

    QTest::mouseClick(rootPage->newCourseButton, Qt::LeftButton);
    QTest::keyClicks(rootPage->courseAddForm->nameInput, newCourseName);
    QTest::mouseClick(rootPage->courseAddDialog->completeButton, Qt::LeftButton);

    QVERIFY(window->stack->currentIndex() == 1);

    CoursePage *coursePage = window->coursePage;

    QVERIFY(coursePage->courseLabel->text() == newCourseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == newCourseName);

    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    QVERIFY(rootPage->scrollLayout->count() == 2);
    QVERIFY(rootPage->idCourseMap.size() == 1);

    auto it = rootPage->idCourseMap.begin();
    QVERIFY(it->second.second == rootPage->scrollLayout->itemAt(0)->widget());
    QVERIFY(it->second.second->course.name == newCourseName);
}