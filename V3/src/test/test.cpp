#include "unistd.h"

#include <iostream>

#include <QLineEdit>
#include <QPushButton>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "database/setup.h"
#include "pages/rootPage.h"
#include "dialogs/formDialog.h"
#include "forms/courseForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"

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

void Test::testOne()
{
    QVERIFY(window->stack->currentIndex() == 0);

    RootPage *rootPage = window->rootPage;

    QTest::mouseClick(rootPage->newCourseButton, Qt::LeftButton);
    QTest::keyClicks(rootPage->courseAddForm->nameInput, "Set Theory");
    QTest::mouseClick(rootPage->courseAddDialog->completeButton, Qt::LeftButton);

    QVERIFY(window->stack->currentIndex() == 1);
}