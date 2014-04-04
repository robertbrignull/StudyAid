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
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *newCourseName = "Set Theory";

    QVERIFY(window->stack->currentIndex() == 0);

    QVERIFY(rootPage->scrollLayout->count() == 1);
    QVERIFY(rootPage->idCourseMap.size() == 0);

    addCourse(newCourseName);

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

void Test::test_editCourse()
{
    RootPage *rootPage = window->rootPage;
    CoursePage *coursePage = window->coursePage;

    const char *oldCourseName = "Set Theory";
    const char *newCourseName = "Linear Algebra";

    addCourse(oldCourseName);
    editCourse(newCourseName);

    std::cout << coursePage->breadCrumbs->currentCourseLabel->text().toStdString() << std::endl;

    QVERIFY(coursePage->courseLabel->text() == newCourseName);
    QVERIFY(coursePage->breadCrumbs->currentCourseLabel->text() == newCourseName);

    QVERIFY(rootPage->idCourseMap.begin()->second.second->course.name == newCourseName);
}

void Test::addCourse(const char *name)
{
    RootPage *rootPage = window->rootPage;

    QTest::mouseClick(rootPage->newCourseButton, Qt::LeftButton);
    rootPage->courseAddForm->nameInput->setText(name);
    QTest::mouseClick(rootPage->courseAddDialog->completeButton, Qt::LeftButton);
}

void Test::editCourse(const char *name)
{
    CoursePage *coursePage = window->coursePage;

    QTest::mouseClick(coursePage->editCourseButton, Qt::LeftButton);
    coursePage->courseEditForm->nameInput->setText(name);
    QTest::mouseClick(coursePage->courseEditDialog->completeButton, Qt::LeftButton);
}