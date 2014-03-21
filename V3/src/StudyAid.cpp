#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include "database/setup.h"
#include "pages/rootPage.h"

#include "StudyAid.h"

StudyAid::StudyAid(QWidget *parent)
    : QWidget(parent)
{
    if (!connectToDatabase()) {
        QCoreApplication::exit();
        exit(1);
    }



    QStackedLayout *layout = new QStackedLayout(this);

    layout->addWidget(new RootPage());

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