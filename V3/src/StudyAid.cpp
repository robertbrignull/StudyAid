#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QFont>

#include <QtTest/QtTest>

#include "model.h"
#include "database/setup.h"
#include "latex/latex.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "pages/proofPage.h"
#include "widgets/resizableStackedWidget.h"

#include "test/test.h"

#include "StudyAid.h"

StudyAid::StudyAid(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    ResizableStackedWidget *stack = new ResizableStackedWidget();
    model = new Model();

    layout->addWidget(stack);

    stack->addWidget(new RootPage(stack, model));
    stack->addWidget(new CoursePage(stack, model));
    stack->addWidget(new FactPage(stack, model));
    stack->addWidget(new ProofPage(stack, model));

    showMaximized();
}

StudyAid::~StudyAid()
{
    delete model;
}

int main(int argc, char **argv)
{
    bool testMode = (argc >= 2 && strncmp(argv[1], "test", 4) == 0);

    initialiseDatabase(testMode);
    initialiseLatex();

    QApplication app(argc, argv);

    QFont font;
    font.setFamily("Helvetica");
    font.setPointSize(18);
    app.setFont(font);

    if (testMode) {
        Test test;
        QTest::qExec(&test);

        return 0;
    }
    else {
        StudyAid window;

        window.setWindowTitle("StudyAid");
        window.show();

        return app.exec();
    }
}