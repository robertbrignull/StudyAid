#pragma once

#include <QObject>

#include "database/structures.h"

struct FactOrProof
{
    bool isFact, isProof;
    Fact fact;
    Proof proof;
};

class RenderQueue : public QObject
{
    Q_OBJECT

public:
    RenderQueue(QObject *parent = 0);

signals:
    void supplyFact(Fact fact);
    void supplyProof(Proof proof);

public slots:
    void queueFact(Fact fact);
    void queueProof(Proof proof);

    void requestText();

private:
    std::list<FactOrProof> queue;
    bool rendererReady;
};