#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <iostream>
#include <sstream>

#include "model.h"

#include "latex/latexRenderThread.h"

inline std::string toString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

bool writeToFile(std::string text, std::string filename)
{
    FILE *file = fopen(filename.c_str(), "w");

    if (file == NULL) {
        return false;
    }

    fprintf(file, "%s", text.c_str());

    fclose(file);

    return true;
}

void deleteFile(std::string filename)
{
    FILE *file = fopen(filename.c_str(), "r");

    if (file != NULL) {
        fclose(file);

        remove(filename.c_str());
    }
}



LatexRenderThread *LatexRenderThread::activeRenderThread = nullptr;
ModelSignaller *LatexRenderThread::modelSignaller = nullptr;
std::string LatexRenderThread::imageDir = "";

LatexRenderThread::LatexRenderThread(QObject *parent)
    : QThread(parent)
{
    emptyQueueMutex.lock();
}

void LatexRenderThread::initialise(ModelSignaller *pModelSignaller, std::string pImageDir)
{
    LatexRenderThread::modelSignaller = pModelSignaller;
    LatexRenderThread::imageDir = pImageDir;
}

LatexRenderThread *LatexRenderThread::getLatexRenderThread()
{
    if (LatexRenderThread::activeRenderThread == nullptr) {
        LatexRenderThread::activeRenderThread = new LatexRenderThread();
        LatexRenderThread::activeRenderThread->start();
    }

    return LatexRenderThread::activeRenderThread;
}

void LatexRenderThread::queueFact(Fact fact)
{
    queueMutex.lock();

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
        factOrProof.fact = fact;
        queue.push_back(factOrProof);
    }

    queueMutex.unlock();
    emptyQueueMutex.unlock();
}

void LatexRenderThread::queueProof(Proof proof)
{
    queueMutex.lock();

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
        factOrProof.isProof = true;
        factOrProof.proof = proof;
        queue.push_back(factOrProof);
    }

    queueMutex.unlock();
    emptyQueueMutex.unlock();
}


void LatexRenderThread::run()
{
    while (true) {
        queueMutex.lock();

        while (queue.empty()) {
            queueMutex.unlock();
            emptyQueueMutex.lock();
            queueMutex.lock();
        }

        FactOrProof factOrProof = queue.front();
        queue.pop_front();

        queueMutex.unlock();

        if (factOrProof.isFact) {
            renderText(factOrProof.fact.statement, LatexRenderThread::imageDir + "/fact/", toString(factOrProof.fact.id));
            std::cout << "Rendered fact " << factOrProof.fact.id << std::endl;
        }
        else {
            renderText(factOrProof.proof.body, LatexRenderThread::imageDir + "/proof/", toString(factOrProof.proof.id));
            std::cout << "Rendered proof " << factOrProof.proof.id << std::endl;
        }
    }
}

int LatexRenderThread::renderText(std::string text, std::string path, std::string filename)
{
    int retVal = 0;

    std::string latex =
        std::string("\\documentclass[a4paper]{article}\n") +
        "\\usepackage{geometry}\n" +
        "\\usepackage[active,tightpage]{preview}\n" +
        "\\usepackage{dsfont}\n" +
        "\\usepackage{amsfonts}\n" +
        "\\usepackage{amsmath}\n" +
        "\\usepackage{amssymb}\n" +
        "\\usepackage{minted}\n" +
        "\\begin{document}\n" +
        "\\begin{preview}\n" +
        "\n" +
        text +
        "\n\n" +
        "\\end{preview}\n" +
        "\\end{document}";

    if (system((std::string("mkdir -p ") + path).c_str())) {
        retVal = 2;
        goto cleanup;
    }

    if (!writeToFile(latex, path + filename + ".latex")) {
        retVal = 2;
        goto cleanup;
    }

    if (system((std::string("cd ") + path + "; pdflatex -shell-escape -halt-on-error -output-directory . " + filename + ".latex > /dev/null").c_str())) {
        retVal = 1;
        goto cleanup;
    }

    if (system((std::string("pdftoppm -png -singlefile -r 250 ") + path + filename + ".pdf " + path + filename + " > /dev/null").c_str())) {
        retVal = 2;
        goto cleanup;
    }

    cleanup:
    // deleteFile(path + filename + ".latex");
    deleteFile(path + filename + ".aux");
    deleteFile(path + filename + ".log");
    deleteFile(path + filename + ".pdf");

    return retVal;
}