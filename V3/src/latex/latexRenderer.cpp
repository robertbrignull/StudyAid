#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <iostream>
#include <sstream>

#include "latex/latex.h"

#include "latex/latexRenderer.h"

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



void LatexRenderer::renderFact(Fact fact)
{
    int result = renderText(fact.statement, getImageDir() + "/fact/", toString(fact.id));
    emit factRendered(fact, (result == 0));
}

void LatexRenderer::renderProof(Proof proof)
{
    int result = renderText(proof.body, getImageDir() + "/proof/", toString(proof.id));
    emit proofRendered(proof, (result == 0));
}

int LatexRenderer::renderText(std::string text, std::string path, std::string filename)
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

    // Should return 0 on success, 1 on latex render error, 2 for some other error
    return retVal;
}