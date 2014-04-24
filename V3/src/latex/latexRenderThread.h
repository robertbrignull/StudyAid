#pragma once

#include <QThread>
#include <QMutex>

#include "database/structures.h"

class ModelSignaller;

struct FactOrProof
{
    bool isFact, isProof;
    Fact fact;
    Proof proof;
};

class LatexRenderThread : public QThread
{
    Q_OBJECT

public:
    LatexRenderThread(QObject *parent = 0);
    ~LatexRenderThread();

    static void initialise(ModelSignaller *modelSignaller, std::string imageDir);
    static LatexRenderThread *getLatexRenderThread();

    void queueFact(Fact fact);
    void queueProof(Proof proof);

signals:
    void factRendered(Fact fact, bool success);
    void proofRendered(Proof proof, bool success);

protected:
    void run();

private:
    int renderText(std::string text, std::string path, std::string filename);



    static LatexRenderThread *activeRenderThread;

    static ModelSignaller *modelSignaller;
    static std::string imageDir;

    std::list<FactOrProof> queue;
    QMutex queueMutex, emptyQueueMutex;
};