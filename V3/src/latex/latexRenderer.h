#pragma once

#include <QObject>

#include "database/structures.h"

class LatexRenderer : public QObject
{
    Q_OBJECT

signals:
    void factRendered(Fact fact, bool success);
    void proofRendered(Proof proof, bool success);

public slots:
    void renderFact(Fact fact);
    void renderProof(Proof proof);

private:
    int renderText(std::string text, std::string path, std::string filename);
};