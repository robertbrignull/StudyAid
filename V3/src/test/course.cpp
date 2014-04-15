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
#include "forms/courseForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/dialog.h"
#include "views/breadCrumbs.h"
#include "views/courseTitleWidget.h"
#include "views/factListView.h"
#include "views/factList.h"

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

void CourseTest::test_addCourse_one()
{
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";

    // Check we're on the root page
    QVERIFY(window->stack->currentIndex() == 0);

    // Check that there are no courses shown
    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);

    // Add our course
    TestUtil::addCourse(window, courseName);

    // Check we're now on the course page
    QVERIFY(window->stack->currentIndex() == 1);

    // Check that the name is shown correctly
    QVERIFY(coursePage->courseLabel->text() == courseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == courseName);

    // Check that the name is correct in the editCourseDialog
    QTest::mouseClick(coursePage->editCourseButton, Qt::LeftButton);
    QVERIFY(coursePage->courseEditForm->nameInput->text() == courseName);
    QTest::mouseClick(coursePage->courseEditDialog->cancelButton, Qt::LeftButton);

    // Check that it has no facts
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Check that one course is shown on the root page
    QVERIFY(rootPage->scrollLayout->count() == 2);
    QVERIFY(rootPage->idCourseMap.size() == 1);

    // Check that the course on the root page has the correct name
    auto it = rootPage->idCourseMap.begin();
    QVERIFY(it->second == rootPage->scrollLayout->itemAt(0)->widget());
    QVERIFY(it->second->course.name == courseName);
}

void CourseTest::test_addCourse_multiple()
{
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *otherCourseName = "Linear Algebra";
    const char *courseName = "Set Theory";

    // Check we're on the root page
    QVERIFY(window->stack->currentIndex() == 0);

    // Check that there are no courses shown
    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);

    // Add our courses
    TestUtil::addCourse(window, otherCourseName);
    TestUtil::addCourse(window, courseName);

    // Check that the name is shown correctly
    QVERIFY(coursePage->courseLabel->text() == courseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == courseName);

    // Check that the name is correct in the editCourseDialog
    QTest::mouseClick(coursePage->editCourseButton, Qt::LeftButton);
    QVERIFY(coursePage->courseEditForm->nameInput->text() == courseName);
    QTest::mouseClick(coursePage->courseEditDialog->cancelButton, Qt::LeftButton);

    // Check that two courses are shown on the root page
    QVERIFY(rootPage->scrollLayout->count() == 3);
    QVERIFY(rootPage->idCourseMap.size() == 2);

    // Check that the courses on the root page have the correct names
    // and are in the correct order
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.name == otherCourseName);
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.name == courseName);
}

void CourseTest::test_editCourse()
{
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *oldCourseName = "Set Theory";
    const char *courseName = "Linear Algebra";

    // Add a course with the old name
    TestUtil::addCourse(window, oldCourseName);

    // Immediately change the name to something else
    TestUtil::editCurrentCourse(window, courseName);

    // Check that the new name is shown everywhere on the course page
    QVERIFY(coursePage->courseLabel->text() == courseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == courseName);

    // Check that the name is correct in the editCourseDialog
    QTest::mouseClick(coursePage->editCourseButton, Qt::LeftButton);
    QVERIFY(coursePage->courseEditForm->nameInput->text() == courseName);
    QTest::mouseClick(coursePage->courseEditDialog->cancelButton, Qt::LeftButton);

    // And is shown correctly on the root page
    QVERIFY(rootPage->idCourseMap.begin()->second->course.name == courseName);
}

void CourseTest::test_editCourseOrdering_moveMode()
{
    RootPage *rootPage = window->rootPage;

    const char *courseName = "Set Theory";

    // Add the course
    TestUtil::addCourse(window, courseName);

    // Check that the correct buttons are visible
    auto courseTitleWidget = rootPage->idCourseMap.begin()->second;
    QVERIFY(courseTitleWidget->moveButton->isHidden() == false);
    QVERIFY(courseTitleWidget->viewCourseButton->isHidden() == false);
    QVERIFY(courseTitleWidget->moveAboveButton->isHidden() == true);
    QVERIFY(courseTitleWidget->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(courseTitleWidget->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(courseTitleWidget->moveButton->isHidden() == true);
    QVERIFY(courseTitleWidget->viewCourseButton->isHidden() == true);
    QVERIFY(courseTitleWidget->moveAboveButton->isHidden() == false);
    QVERIFY(courseTitleWidget->moveBelowButton->isHidden() == false);

    // Click the moveAboveButton
    QTest::mouseClick(courseTitleWidget->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(courseTitleWidget->moveButton->isHidden() == false);
    QVERIFY(courseTitleWidget->viewCourseButton->isHidden() == false);
    QVERIFY(courseTitleWidget->moveAboveButton->isHidden() == true);
    QVERIFY(courseTitleWidget->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(courseTitleWidget->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(courseTitleWidget->moveButton->isHidden() == true);
    QVERIFY(courseTitleWidget->viewCourseButton->isHidden() == true);
    QVERIFY(courseTitleWidget->moveAboveButton->isHidden() == false);
    QVERIFY(courseTitleWidget->moveBelowButton->isHidden() == false);

    // Click the moveBelowButton
    QTest::mouseClick(courseTitleWidget->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(courseTitleWidget->moveButton->isHidden() == false);
    QVERIFY(courseTitleWidget->viewCourseButton->isHidden() == false);
    QVERIFY(courseTitleWidget->moveAboveButton->isHidden() == true);
    QVERIFY(courseTitleWidget->moveBelowButton->isHidden() == true);
}

void CourseTest::test_editCourseOrdering_moveAbove()
{
    RootPage *rootPage = window->rootPage;

    const char *courseName1 = "Set Theory";
    const char *courseName2 = "Linear Algebra";

    // Add our course
    TestUtil::addCourse(window, courseName1);
    TestUtil::addCourse(window, courseName2);

    // Move the second course above the first
    QTest::mouseClick(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->moveAboveButton, Qt::LeftButton);

    // Check that the courses are now in the correct order
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.name == courseName2);
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.name == courseName1);

    // Check that the orderings are valid
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.ordering < ((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.ordering);
}

void CourseTest::test_editCourseOrdering_moveBelow()
{
    RootPage *rootPage = window->rootPage;

    const char *courseName1 = "Set Theory";
    const char *courseName2 = "Linear Algebra";

    // Add our course
    TestUtil::addCourse(window, courseName1);
    TestUtil::addCourse(window, courseName2);

    // Move the first course below the second
    QTest::mouseClick(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the courses are now in the correct order
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.name == courseName2);
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.name == courseName1);

    // Check that the orderings are valid
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.ordering < ((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.ordering);
}

void CourseTest::test_editCourseOrdering_moveBetween()
{
    RootPage *rootPage = window->rootPage;

    const char *courseName1 = "Set Theory";
    const char *courseName2 = "Linear Algebra";
    const char *courseName3 = "Complex Analysis";

    // Add our course
    TestUtil::addCourse(window, courseName1);
    TestUtil::addCourse(window, courseName2);
    TestUtil::addCourse(window, courseName3);

    // Move the first course below the second
    QTest::mouseClick(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the courses are now in the correct order
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.name == courseName2);
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.name == courseName1);
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(2)->widget())->course.name == courseName3);

    // Check that the orderings are valid
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(0)->widget())->course.ordering < ((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.ordering);
    QVERIFY(((CourseTitleWidget*) rootPage->scrollLayout->itemAt(1)->widget())->course.ordering < ((CourseTitleWidget*) rootPage->scrollLayout->itemAt(2)->widget())->course.ordering);
}

void CourseTest::test_deleteCourse_all()
{
    RootPage *rootPage = window->rootPage;

    const char *courseName = "Complex Analysis";

    // Add a course
    TestUtil::addCourse(window, courseName);

    // Immediately delete the course
    TestUtil::deleteCurrentCourse(window);

    // Check that we're back on the root page
    QVERIFY(window->stack->currentIndex() == 0);

    // Check that no courses are shown
    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);
}

void CourseTest::test_deleteCourse_one()
{
    RootPage *rootPage = window->rootPage;

    const char *courseName = "Complex Analysis";
    const char *otherCourseName = "Linear Algebra";

    // Add our courses
    TestUtil::addCourse(window, otherCourseName);
    TestUtil::addCourse(window, courseName);

    // Immediately delete the course
    TestUtil::deleteCurrentCourse(window);

    // Check that we're back on the root page
    QVERIFY(window->stack->currentIndex() == 0);

    // Check that one course is shown
    QVERIFY(rootPage->scrollLayout->count() == 2);
    QVERIFY(rootPage->idCourseMap.size() == 1);

    // Check that the name is correct
    auto it = rootPage->idCourseMap.begin();
    QVERIFY(it->second->course.name == otherCourseName);
}