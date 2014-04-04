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
#include "dialogs/deleteDialog.h"
#include "forms/courseForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/breadCrumbs.h"
#include "widgets/courseTitleWidget.h"
#include "widgets/factListView.h"
#include "widgets/factList.h"

#include "test/testUtil.h"

#include "test/course.h"

void CourseTest::init()
{
    clearTestDatabase();

    window = new StudyAid();
}

void CourseTest::cleanup()
{
    delete window;
}

void CourseTest::test_addCourse()
{
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *newCourseName = "Set Theory";

    QVERIFY(window->stack->currentIndex() == 0);

    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);

    TestUtil::addCourse(window, newCourseName);

    QVERIFY(window->stack->currentIndex() == 1);

    QVERIFY(coursePage->courseLabel->text() == newCourseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == newCourseName);

    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    QVERIFY(rootPage->scrollLayout->count() == 2);
    QVERIFY(rootPage->idCourseMap.size() == 1);

    auto it = rootPage->idCourseMap.begin();
    QVERIFY(it->second.second == rootPage->scrollLayout->itemAt(0)->widget());
    QVERIFY(it->second.second->course.name == newCourseName);
}

void CourseTest::test_editCourse()
{
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *oldCourseName = "Set Theory";
    const char *newCourseName = "Linear Algebra";

    TestUtil::addCourse(window, oldCourseName);
    TestUtil::editCurrentCourse(window, newCourseName);

    QVERIFY(coursePage->courseLabel->text() == newCourseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == newCourseName);

    QVERIFY(rootPage->idCourseMap.begin()->second.second->course.name == newCourseName);
}

void CourseTest::test_deleteCourse()
{
    RootPage *rootPage = window->rootPage;

    const char *newCourseName = "Complex Algebra";

    TestUtil::addCourse(window, newCourseName);
    TestUtil::deleteCurrentCourse(window);

    QVERIFY(window->stack->currentIndex() == 0);

    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);
}