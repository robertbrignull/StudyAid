#include <iostream>

#include "renderQueue.h"

RenderQueue::RenderQueue(QObject *parent)
    : QObject(parent)
{
    rendererReady = true;
}

void RenderQueue::queueFact(Fact fact)
{
    if (queue.empty() && rendererReady) {
        emit supplyFact(fact);
    }
    else {
        bool found = false;
        for (auto it = queue.begin(); it != queue.end(); it++) {
            if ((*it).isFact && (*it).fact.id == fact.id) {
                (*it).fact = fact;
                found = true;
                break;
            }
        }

        if (!found) {
            FactOrProof factOrProof;
            factOrProof.isFact = true;
            factOrProof.isProof = false;
            factOrProof.fact = fact;
            queue.push_back(factOrProof);
        }
    }
    
    rendererReady = false;
}

void RenderQueue::queueProof(Proof proof)
{
    if (queue.empty() && rendererReady) {
        emit supplyProof(proof);
    }
    else {
        bool found = false;
        for (auto it = queue.begin(); it != queue.end(); it++) {
            if ((*it).isProof && (*it).proof.id == proof.id) {
                (*it).proof = proof;
                found = true;
                break;
            }
        }

        if (!found) {
            FactOrProof factOrProof;
            factOrProof.isFact = false;
            factOrProof.isProof = true;
            factOrProof.proof = proof;
            queue.push_back(factOrProof);
        }
    }
    
    rendererReady = false;
}

void RenderQueue::requestText()
{
    if (queue.empty()) {
        rendererReady = true;
    }
    else {
        FactOrProof factOrProof = queue.front();
        queue.pop_front();

        if (factOrProof.isFact) {
            emit supplyFact(factOrProof.fact);
        }
        else if (factOrProof.isProof) {
            emit supplyProof(factOrProof.proof);
        }
    }
}