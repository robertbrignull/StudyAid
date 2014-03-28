#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QFont>

#include "database/setup.h"
#include "pages/rootPage.h"
#include "pages/coursePage.h"
#include "pages/factPage.h"
#include "pages/proofPage.h"
#include "widgets/resizableStackedWidget.h"

#include "StudyAid.h"

StudyAid::StudyAid(QWidget *parent)
    : QWidget(parent)
{
    if (!connectToDatabase()) {
        QCoreApplication::exit();
        exit(1);
    }



    QHBoxLayout *layout = new QHBoxLayout(this);

    ResizableStackedWidget *stack = new ResizableStackedWidget();
    connect(stack, SIGNAL(currentChanged(int)), stack, SLOT(onCurrentChanged(int)));

    layout->addWidget(stack);

    stack->addWidget(new RootPage(stack));
    stack->addWidget(new CoursePage(stack));
    stack->addWidget(new FactPage(stack));
    stack->addWidget(new ProofPage(stack));

    showMaximized();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QFont font;
    font.setFamily("Helvetica");
    font.setPointSize(18);
    app.setFont(font);

    StudyAid window;

    window.setWindowTitle("StudyAid");
    window.show();

    return app.exec();
}