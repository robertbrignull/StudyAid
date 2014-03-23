#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>

#include "database/setup.h"
#include "pages/rootPage.h"
#include "widgets/layout/resizableStackedWidget.h"

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
    layout->addWidget(stack);

    stack->addWidget(new RootPage(stack));

    showMaximized();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    StudyAid window;

    window.move(300, 300);
    window.setWindowTitle("StudyAid");
    window.show();

    return app.exec();
}