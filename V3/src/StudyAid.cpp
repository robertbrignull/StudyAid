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

#include "test/runner.h"

#include "StudyAid.h"

StudyAid::StudyAid(ModelSignaller *modelSignaller, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    stack = new ResizableStackedWidget();
    model = new Model(modelSignaller);

    rootPage = new RootPage(stack, model);
    coursePage = new CoursePage(stack, model);
    factPage = new FactPage(stack, model);
    proofPage = new ProofPage(stack, model);

    layout->addWidget(stack);

    stack->addWidget(rootPage);
    stack->addWidget(coursePage);
    stack->addWidget(factPage);
    stack->addWidget(proofPage);

    showMaximized();



    connect(rootPage, SIGNAL(requestNewWindow()), this, SIGNAL(requestNewWindow()));
}

StudyAid::~StudyAid()
{
    delete model;
}

StudyAidController::StudyAidController()
{
    modelSignaller = new ModelSignaller();
}

StudyAidController::~StudyAidController()
{
    delete modelSignaller;
}

void StudyAidController::openNewWindow()
{
    StudyAid *window = new StudyAid(modelSignaller);

    window->setWindowTitle("StudyAid");
    window->show();

    connect(window, SIGNAL(requestNewWindow()), this, SLOT(openNewWindow()));
}

int main(int argc, char **argv)
{
    const char *database = (argc >= 2 ? argv[1] : "default");

    bool testMode = (argc >= 2 && strncmp(argv[1], "test", 4) == 0);

    initialiseConnection(database);
    initialiseBackup();
    initialiseLatex(database);

    if (argc >= 3 && strncmp(argv[2], "render-all", 12) == 0) {
        renderAll();
        exit(0);
    }

    QApplication app(argc, argv);

    QFont font;
    font.setFamily("Helvetica");
    font.setPointSize(18);
    app.setFont(font);

    if (testMode) {
        runAllTests();

        return 0;
    }
    else {
        StudyAidController controller;
        controller.openNewWindow();

        return app.exec();
    }
}