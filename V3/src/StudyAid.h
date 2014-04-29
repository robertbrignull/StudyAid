#pragma once

#include <QWidget>

#include "database/structures.h"

class ModelSignaller;
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
    StudyAid(ModelSignaller *modelSignaller, QWidget *parent = 0);
    ~StudyAid();



    ResizableStackedWidget *stack;

    RootPage *rootPage;
    CoursePage *coursePage;
    FactPage *factPage;
    ProofPage *proofPage;

    Model *model;

signals:
    void requestNewWindow(int pageIndex, Course course, Fact fact, Proof proof);
};

class StudyAidController : public QWidget
{
    Q_OBJECT

public:
    StudyAidController();
    ~StudyAidController();



    ModelSignaller *modelSignaller;

public slots:
    void openNewWindow(int pageIndex, Course course, Fact fact, Proof proof);
};