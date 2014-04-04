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

    // Check we're on the root page
    QVERIFY(window->stack->currentIndex() == 0);

    // Check that there are no courses shown
    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);

    // Add our course
    TestUtil::addCourse(window, newCourseName);

    // Check we're now on the course page
    QVERIFY(window->stack->currentIndex() == 1);

    // Check that the name is shown correctly
    QVERIFY(coursePage->courseLabel->text() == newCourseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == newCourseName);

    // Check that it has no facts
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Check that one course is shown on the root page
    QVERIFY(rootPage->scrollLayout->count() == 2);
    QVERIFY(rootPage->idCourseMap.size() == 1);

    // Check that the course on the root page has the correct name
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

    // Add a course with the old name
    TestUtil::addCourse(window, oldCourseName);

    // Immediately change the name to something else
    TestUtil::editCurrentCourse(window, newCourseName);

    // Check that the new name is shown everywhere on the course page
    QVERIFY(coursePage->courseLabel->text() == newCourseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == newCourseName);

    // And is shown correctly on the root page
    QVERIFY(rootPage->idCourseMap.begin()->second.second->course.name == newCourseName);
}

void CourseTest::test_deleteCourse()
{
    RootPage *rootPage = window->rootPage;

    const char *newCourseName = "Complex Algebra";

    // Add a course
    TestUtil::addCourse(window, newCourseName);

    // Immediately delete the course
    TestUtil::deleteCurrentCourse(window);

    // Check that we're back on the root page
    QVERIFY(window->stack->currentIndex() == 0);

    // Check that no courses are shown
    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);
}