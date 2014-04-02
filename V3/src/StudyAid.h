#pragma once

#include <QWidget>

class Model;
class ResizableStackedWidget;
class RootPage;
class CoursePage;
class FactPage;
class ProofPage;

class StudyAid : public QWidget
{
    Q_OBJECT

public:
    StudyAid(QWidget *parent = 0);
    ~StudyAid();



    ResizableStackedWidget *stack;

    RootPage *rootPage;
    CoursePage *coursePage;
    FactPage *factPage;
    ProofPage *proofPage;

    Model *model;
};