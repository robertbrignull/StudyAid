#include <iostream>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <QtTest/QtTest>

#include "StudyAid.h"
#include "model.h"
#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "forms/sectionForm.h"
#include "widgets/resizableStackedWidget.h"
#include "widgets/imageButton.h"
#include "widgets/clickableQLabel.h"
#include "widgets/dialog.h"
#include "views/breadCrumbs.h"
#include "views/courseTitleWidget.h"
#include "views/factListView.h"
#include "views/factList.h"
#include "views/sectionPickerWidget.h"
#include "views/expandingFactWidget.h"

#include "test/testUtil.h"

#include "test/section.h"

void SectionTest::init()
{
    clearTestDatabase();

    modelSignaller = new ModelSignaller();
    window = new StudyAid(modelSignaller);
}

void SectionTest::cleanup()
{
    delete window;
    delete modelSignaller;
}

void SectionTest::test_addSection_toRoot()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";

    // Add our course
    TestUtil::addCourse(window, courseName);

    // Check that the fact list is still empty
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 0);

    // Check that the root section has the correct label
    QVERIFY(coursePage->sectionPicker->sectionLabel->text() == "All");

    // Add our new section
    TestUtil::addFact(window, sectionName, "Section");

    // Check that the new section is shown in the section picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 1);

    // Check it has the correct name
    auto sectionPicker = coursePage->sectionPicker->idSectionPickerMap.begin()->second;
    QVERIFY(sectionPicker->sectionLabel->text() == sectionName);

    // Check that the new section has no children
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 0);

    // Check that the fact list has updated
    FactList *factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 0);

    // Check that the section in the fact list has the correct name and no children
    factList = factList->idChildSectionMap.begin()->second;
    QVERIFY(factList->sectionNameLabel->text() == sectionName);
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 0);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 0);
}

void SectionTest::test_addSection_toSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *parentSectionName = "Cardinal Numbers";
    const char *childSectionName = "Infinities";

    // Add our course and sections
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, parentSectionName, "Section");
    TestUtil::addFactToSection(window, childSectionName, "Section", parentSectionName);

    // Check that each section has the correct name and number of children
    auto sectionPicker = coursePage->sectionPicker;

    QVERIFY(sectionPicker->sectionLabel->text() == "All");
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 1);

    sectionPicker = sectionPicker->idSectionPickerMap.begin()->second;

    QVERIFY(sectionPicker->sectionLabel->text() == parentSectionName);
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 1);

    sectionPicker = sectionPicker->idSectionPickerMap.begin()->second;

    QVERIFY(sectionPicker->sectionLabel->text() == childSectionName);
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 0);

    // Check that the fact list is correct
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 0);

    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == parentSectionName);
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 0);

    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == childSectionName);
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 0);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 0);
}

void SectionTest::test_selectSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";
    const char *level0FactName = "level 0 fact";
    const char *level0FactType = "Theorem";
    const char *level1FactName = "level 1 fact";
    const char *level1FactType = "Theorem";

    // Add our course and sections and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, level0FactName, level0FactType);
    TestUtil::addFact(window, sectionName, "Section");
    TestUtil::addFactToSection(window, level1FactName, level1FactType, sectionName);

    // Select the section
    TestUtil::selectSection(window, sectionName);

    // Check that the fact list has 1 element
    QVERIFY(coursePage->factListView->currentFactList->idChildMap.size() == 1);

    // Check that that element has the correct name
    ExpandingFactWidget *factWidget = (ExpandingFactWidget*) coursePage->factListView->currentFactList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == level1FactName);

    // Select the root section again
    TestUtil::selectSection(window, "All");

    // Check that the fact list now has two elements, one of which is a section
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 2);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 1);

    // Check that the first element is not a section
    QVERIFY(factList->layout->itemAt(0)->widget() == factList->idChildFactMap.begin()->second);

    // Check that the first element is a fact of the correct name
    QVERIFY(factList->idChildFactMap.begin()->second->nameLabel->text() == level0FactName);

    // Check that the second is a section
    QVERIFY(factList->layout->itemAt(1)->widget() == factList->idChildSectionMap.begin()->second);

    // Check that the section has the correct name
    factList = factList->idChildSectionMap.begin()->second;
    QVERIFY(factList->sectionNameLabel->text() == sectionName);

    // Check that the section has one child which is not a section
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 1);

    // Check that the first element is a fact of the correct name
    factWidget = (ExpandingFactWidget*) factList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == level1FactName);
}

void SectionTest::test_editSection_form()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *sectionName = "Cardinal Numbers";

    // Add our course and section
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName, "Section");

    // Open the dialog
    QTest::mouseClick(coursePage->sectionPicker->idSectionPickerMap.begin()->second->editSectionButton, Qt::LeftButton);

    // Check that the dialog is showing
    QVERIFY(coursePage->sectionEditDialog->isHidden() == false);

    // Check that the accept button is enabled
    QVERIFY(coursePage->sectionEditDialog->confirmButton->isEnabled() == true);

    // Change the name to be empty
    coursePage->sectionEditForm->nameInput->setText("");

    // Check that the accept button is disabled
    QVERIFY(coursePage->sectionEditDialog->confirmButton->isEnabled() == false);

    // Change the name to be non-empty
    coursePage->sectionEditForm->nameInput->setText(sectionName);

    // Check that the accept button is disabled
    QVERIFY(coursePage->sectionEditDialog->confirmButton->isEnabled() == true);

    // Close the dialog
    QTest::mouseClick(coursePage->sectionEditDialog->cancelButton, Qt::LeftButton);

    // Check that the dialog closed
    QVERIFY(coursePage->sectionEditDialog->isHidden() == true);
}

void SectionTest::test_editSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";
    const char *newSectionName = "Infinities";

    // Add our course and section
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName, "Section");

    // Immediately change the name to something else
    TestUtil::editSection(window, newSectionName, sectionName);

    // Check that the new section is shown in the section picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 1);

    // Check it has the correct name
    auto sectionPicker = coursePage->sectionPicker->idSectionPickerMap.begin()->second;
    QVERIFY(sectionPicker->sectionLabel->text() == newSectionName);

    // Check that the new section has no children
    QVERIFY(sectionPicker->idSectionPickerMap.size() == 0);

    // Check that the fact list has updated
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 0);

    // Check that the section in the fact list has the correct name and no children
    factList = (FactList*) factList->idChildMap.begin()->second.second;
    QVERIFY(factList->sectionNameLabel->text() == newSectionName);
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 0);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 0);
}

void SectionTest::test_editSectionOrdering_moveMode()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *sectionName1 = "section 1";
    const char *sectionName2 = "section 2";

    // Add the course and section
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName1, "Section");
    TestUtil::addFact(window, sectionName2, "Section");

    // Check that the correct buttons are visible
    auto it = coursePage->factListView->currentFactList->idChildSectionMap.begin();
    auto factList1 = it->second;
    it++;
    auto factList2 = it->second;

    QVERIFY(factList1->moveButton->isHidden() == false);
    QVERIFY(factList1->moveAboveButton->isHidden() == true);
    QVERIFY(factList1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(factList2->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(factList1->moveButton->isHidden() == true);
    QVERIFY(factList1->moveAboveButton->isHidden() == false);
    QVERIFY(factList1->moveBelowButton->isHidden() == false);

    // Click the moveAboveButton
    QTest::mouseClick(factList2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(factList1->moveButton->isHidden() == false);
    QVERIFY(factList1->moveAboveButton->isHidden() == true);
    QVERIFY(factList1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(factList2->moveButton, Qt::LeftButton);

    // Check that the other buttons are visible
    QVERIFY(factList1->moveButton->isHidden() == true);
    QVERIFY(factList1->moveAboveButton->isHidden() == false);
    QVERIFY(factList1->moveBelowButton->isHidden() == false);

    // Click the moveBelowButton
    QTest::mouseClick(factList2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(factList1->moveButton->isHidden() == false);
    QVERIFY(factList1->moveAboveButton->isHidden() == true);
    QVERIFY(factList1->moveBelowButton->isHidden() == true);

    // Click the move button
    QTest::mouseClick(factList2->moveButton, Qt::LeftButton);

    // Check that only the move button is visible
    QVERIFY(factList2->moveButton->isHidden() == false);
    QVERIFY(factList2->moveAboveButton->isHidden() == true);
    QVERIFY(factList2->moveBelowButton->isHidden() == true);

    // Click the move cancel button
    QTest::mouseClick(factList2->moveAboveButton, Qt::LeftButton);

    // Check that the original buttons are visible
    QVERIFY(factList2->moveButton->isHidden() == false);
    QVERIFY(factList2->moveAboveButton->isHidden() == true);
    QVERIFY(factList2->moveBelowButton->isHidden() == true);
}

void SectionTest::test_editSectionOrdering_moveAbove()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *sectionName1 = "section 1";
    const char *sectionName2 = "section 2";

    // Add the course and sections
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName1, "Section");
    TestUtil::addFact(window, sectionName2, "Section");

    // Move the second section above the first
    auto currentFactListLayout = coursePage->factListView->currentFactList->layout;
    QTest::mouseClick(((FactList*) currentFactListLayout->itemAt(1)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((FactList*) currentFactListLayout->itemAt(0)->widget())->moveAboveButton, Qt::LeftButton);

    // Check that the sections are now in the correct order
    QVERIFY(((FactList*) currentFactListLayout->itemAt(0)->widget())->fact.name == sectionName2);
    QVERIFY(((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.name == sectionName1);

    // Check that the orderings are valid
    QVERIFY(((FactList*) currentFactListLayout->itemAt(0)->widget())->fact.ordering < ((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.ordering);

    // Check that the section picker updated
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 2);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(1)->widget())->sectionLabel->text() == sectionName2);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(2)->widget())->sectionLabel->text() == sectionName1);
}

void SectionTest::test_editSectionOrdering_moveBelow()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *sectionName1 = "section 1";
    const char *sectionName2 = "section 2";

    // Add our course and sections
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName1, "Section");
    TestUtil::addFact(window, sectionName2, "Section");

    // Move the first section below the second
    auto currentFactListLayout = coursePage->factListView->currentFactList->layout;
    QTest::mouseClick(((FactList*) currentFactListLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((FactList*) currentFactListLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the sections are now in the correct order
    QVERIFY(((FactList*) currentFactListLayout->itemAt(0)->widget())->fact.name == sectionName2);
    QVERIFY(((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.name == sectionName1);

    // Check that the orderings are valid
    QVERIFY(((FactList*) currentFactListLayout->itemAt(0)->widget())->fact.ordering < ((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.ordering);

    // Check that the section picker updated
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 2);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(1)->widget())->sectionLabel->text() == sectionName2);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(2)->widget())->sectionLabel->text() == sectionName1);
}

void SectionTest::test_editSectionOrdering_moveBetween()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *sectionName1 = "section 1";
    const char *sectionName2 = "section 2";
    const char *sectionName3 = "section 3";

    // Add our course and sections
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName1, "Section");
    TestUtil::addFact(window, sectionName2, "Section");
    TestUtil::addFact(window, sectionName3, "Section");

    // Move the first section below the second
    auto currentFactListLayout = coursePage->factListView->currentFactList->layout;
    QTest::mouseClick(((FactList*) currentFactListLayout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((FactList*) currentFactListLayout->itemAt(1)->widget())->moveBelowButton, Qt::LeftButton);

    // Check that the sections are now in the correct order
    QVERIFY(((FactList*) currentFactListLayout->itemAt(0)->widget())->fact.name == sectionName2);
    QVERIFY(((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.name == sectionName1);
    QVERIFY(((FactList*) currentFactListLayout->itemAt(2)->widget())->fact.name == sectionName3);

    // Check that the orderings are valid
    QVERIFY(((FactList*) currentFactListLayout->itemAt(0)->widget())->fact.ordering < ((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.ordering);
    QVERIFY(((FactList*) currentFactListLayout->itemAt(1)->widget())->fact.ordering < ((FactList*) currentFactListLayout->itemAt(2)->widget())->fact.ordering);

    // Check that the section picker updated
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 3);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(1)->widget())->sectionLabel->text() == sectionName2);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(2)->widget())->sectionLabel->text() == sectionName1);
    QVERIFY(((SectionPickerWidget*) coursePage->sectionPicker->layout->itemAt(3)->widget())->sectionLabel->text() == sectionName3);
}

void SectionTest::test_editSectionOrdering_factIntoSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *level0FactName = "level 0 fact";
    const char *level0FactType = "Axiom";
    const char *level1FactName = "level 1 fact";
    const char *level1FactType = "Axiom";
    const char *sectionName = "section";

    // Add our course, section and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, level0FactName, level0FactType);
    TestUtil::addFact(window, sectionName, "Section");
    TestUtil::addFactToSection(window, level1FactName, level1FactType, sectionName);

    // Move the outer fact inside the section
    auto factList = coursePage->factListView->currentFactList;
    QTest::mouseClick(((ExpandingFactWidget*) factList->layout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(factList->idChildSectionMap.begin()->second->idChildFactMap.begin()->second->moveAboveButton, Qt::LeftButton);

    // Check that the fact has moved
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 0);

    factList = factList->idChildSectionMap.begin()->second;
    QVERIFY(factList->layout->count() == 3);
    QVERIFY(factList->idChildMap.size() == 2);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 2);

    // Check that the facts are in the correct order
    QVERIFY(((ExpandingFactWidget *) factList->layout->itemAt(1)->widget())->fact.name == level0FactName);
    QVERIFY(((ExpandingFactWidget *) factList->layout->itemAt(2)->widget())->fact.name == level1FactName);
}

void SectionTest::test_editSectionOrdering_sectionIntoSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName = "fact";
    const char *factType = "Axiom";
    const char *sectionName0 = "section 0";
    const char *sectionName1 = "section 1";

    // Add our course, section and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName0, "Section");
    TestUtil::addFact(window, sectionName1, "Section");
    TestUtil::addFactToSection(window, factName, factType, sectionName1);

    // Move one section inside the other section
    auto factList = coursePage->factListView->currentFactList;
    QTest::mouseClick(((FactList*) factList->layout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((FactList*) factList->layout->itemAt(1)->widget())->idChildFactMap.begin()->second->moveAboveButton, Qt::LeftButton);

    // Check that the fact has moved
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 0);

    factList = factList->idChildSectionMap.begin()->second;
    QVERIFY(factList->layout->count() == 3);
    QVERIFY(factList->idChildMap.size() == 2);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 1);

    // Check that the facts are in the correct order
    QVERIFY(factList->layout->itemAt(1)->widget() == (QWidget*) factList->idChildSectionMap.begin()->second);
    QVERIFY(factList->layout->itemAt(2)->widget() == (QWidget*) factList->idChildFactMap.begin()->second);
}

void SectionTest::test_editSectionOrdering_factOutOfSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *level0FactName = "level 0 fact";
    const char *level0FactType = "Axiom";
    const char *level1FactName = "level 1 fact";
    const char *level1FactType = "Axiom";
    const char *sectionName = "section";

    // Add our course, section and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, level0FactName, level0FactType);
    TestUtil::addFact(window, sectionName, "Section");
    TestUtil::addFactToSection(window, level1FactName, level1FactType, sectionName);

    // Move the outer fact inside the section
    auto factList = coursePage->factListView->currentFactList;
    QTest::mouseClick(((ExpandingFactWidget*) factList->layout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(factList->idChildSectionMap.begin()->second->idChildFactMap.begin()->second->moveAboveButton, Qt::LeftButton);

    // Move the fact back out again
    QTest::mouseClick(((ExpandingFactWidget*) factList->idChildSectionMap.begin()->second->layout->itemAt(1)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(factList->idChildSectionMap.begin()->second->moveAboveButton, Qt::LeftButton);

    // Check that the fact has moved
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 2);
    QVERIFY(factList->idChildSectionMap.size() == 1);
    QVERIFY(factList->idChildFactMap.size() == 1);

    factList = factList->idChildSectionMap.begin()->second;
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 1);

    // Check that the facts are in the correct order
    factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->itemAt(0)->widget() == (QWidget*) factList->idChildFactMap.begin()->second);
    QVERIFY(factList->idChildFactMap.begin()->second->fact.name == level0FactName);
    QVERIFY(factList->layout->itemAt(1)->widget() == (QWidget*) factList->idChildSectionMap.begin()->second);

    factList = factList->idChildSectionMap.begin()->second;
    QVERIFY(factList->layout->itemAt(1)->widget() == (QWidget*) factList->idChildFactMap.begin()->second);
    QVERIFY(factList->idChildFactMap.begin()->second->fact.name == level1FactName);
}

void SectionTest::test_editSectionOrdering_sectionOutOfSection()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Theory";
    const char *factName = "fact";
    const char *factType = "Axiom";
    const char *sectionName0 = "section 0";
    const char *sectionName1 = "section 1";

    // Add our course, section and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName0, "Section");
    TestUtil::addFact(window, sectionName1, "Section");
    TestUtil::addFactToSection(window, factName, factType, sectionName1);

    // Move one section inside the other section
    auto factList = coursePage->factListView->currentFactList;
    QTest::mouseClick(((FactList*) factList->layout->itemAt(0)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(((FactList*) factList->layout->itemAt(1)->widget())->idChildFactMap.begin()->second->moveAboveButton, Qt::LeftButton);

    // Move the section back out again
    QTest::mouseClick(((FactList*) factList->idChildSectionMap.begin()->second->layout->itemAt(1)->widget())->moveButton, Qt::LeftButton);
    QTest::mouseClick(factList->idChildSectionMap.begin()->second->moveAboveButton, Qt::LeftButton);

    // Check that the fact has moved
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 2);
    QVERIFY(factList->idChildSectionMap.size() == 2);
    QVERIFY(factList->idChildFactMap.size() == 0);

    factList = (FactList*) factList->layout->itemAt(1)->widget();
    QVERIFY(factList->layout->count() == 2);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 1);

    // Check that the facts are in the correct order
    factList = coursePage->factListView->currentFactList;
    QVERIFY(((FactList*) factList->layout->itemAt(0)->widget())->sectionNameLabel->text() == sectionName0);
    QVERIFY(((FactList*) factList->layout->itemAt(1)->widget())->sectionNameLabel->text() == sectionName1);

    factList = (FactList*) factList->layout->itemAt(1)->widget();
    QVERIFY(factList->layout->itemAt(1)->widget() == (QWidget*) factList->idChildFactMap.begin()->second);
    QVERIFY(factList->idChildFactMap.begin()->second->fact.name == factName);
}

void SectionTest::test_deleteSection_empty()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";

    // Add our course and section
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, sectionName, "Section");

    // Immediately delete the section
    TestUtil::deleteSection(window, sectionName);

    // Check that the course page shows no facts
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->count() == 0);
    QVERIFY(factList->idChildMap.size() == 0);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 0);

    // Check that the no sections are shown in the picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 0);
}

void SectionTest::test_deleteSection_notEmpty()
{
    CoursePage *coursePage = window->coursePage;

    const char *courseName = "Set Thoery";
    const char *sectionName = "Cardinal Numbers";
    const char *level0FactName = "level 0 fact";
    const char *level0FactType = "Theorem";
    const char *level1FactName = "level 1 fact";
    const char *level1FactType = "Theorem";

    // Add our course and section and facts
    TestUtil::addCourse(window, courseName);
    TestUtil::addFact(window, level0FactName, level0FactType);
    TestUtil::addFact(window, sectionName, "Section");
    TestUtil::addFactToSection(window, level1FactName, level1FactType, sectionName);

    // Immediately delete the section
    TestUtil::deleteSection(window, sectionName);

    // Check that the course page shows one fact
    auto factList = coursePage->factListView->currentFactList;
    QVERIFY(factList->layout->count() == 1);
    QVERIFY(factList->idChildMap.size() == 1);
    QVERIFY(factList->idChildSectionMap.size() == 0);
    QVERIFY(factList->idChildFactMap.size() == 1);

    // Check that the fact is the correct one
    ExpandingFactWidget *factWidget = (ExpandingFactWidget*) coursePage->factListView->currentFactList->idChildMap.begin()->second.second;
    QVERIFY(factWidget->nameLabel->text() == level0FactName);

    // Check that the no sections are shown in the picker
    QVERIFY(coursePage->sectionPicker->idSectionPickerMap.size() == 0);
}