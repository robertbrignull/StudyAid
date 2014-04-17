#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "database/methods.h"

#include "latex/latex.h"

std::string imageDir;

std::string toString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void initialiseLatex(const char *database)
{
    imageDir = std::string(getpwuid(getuid())->pw_dir) + "/.StudyAidV3/" + database + "/";
}

std::string getFactImageFilename(Fact fact)
{
    return imageDir + "/fact/" + toString(fact.id) + ".png";
}

std::string getProofImageFilename(Proof proof)
{
    return imageDir + "/proof/" + toString(proof.id) + ".png";
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

int renderText(std::string text, std::string path, std::string filename)
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
        "\\begin{document}\n" +
        "\\begin{preview}\n" +
        "\\ \n" +
        text +
        "\n\n" +
        "\\end{preview}\n" +
        "\\end{document}\n";

    if (system((std::string("mkdir -p ") + path).c_str())) {
        retVal = 2;
        goto cleanup;
    }

    if (!writeToFile(latex, path + filename + ".latex")) {
        retVal = 2;
        goto cleanup;
    }

    if (system((std::string("pdflatex -halt-on-error -output-directory ") + path + " " + filename + ".latex > /dev/null").c_str())) {
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

int renderFact(Fact fact)
{
    return renderText(fact.statement, imageDir + "fact/", toString(fact.id));
}

int renderProof(Proof proof)
{
    return renderText(proof.body, imageDir + "proof/", toString(proof.id));
}

void recursivelyRenderFact(Fact fact)
{
    if (fact.type == "Section") {
        std::vector<Fact> facts = findChildFacts(fact.id);
        for (size_t i = 0; i < facts.size(); i++) {
            recursivelyRenderFact(facts[i]);
        }
    }
    else {
        std::cout << "Rendering fact " << fact.id << std::endl;

        renderFact(fact);

        std::vector<Proof> proofs = findProofsForFact(fact.id);
        for (size_t i = 0; i < proofs.size(); i++) {
            renderProof(proofs[i]);
        }
    }
}

void renderAll()
{
    // First delete any rendered images
    if (system((std::string("rm -f ") + imageDir + "/fact/* " + imageDir + "/proof/*").c_str())) {
        std::cout << "Could not delete rendered images" << std::endl;
    }

    std::vector<Course> courses = findAllCourses();
    for (size_t i = 0; i < courses.size(); i++) {
        recursivelyRenderFact(findFact(courses[i].root_fact));
    }
}