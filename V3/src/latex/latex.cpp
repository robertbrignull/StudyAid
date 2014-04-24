#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "database/methods.h"
#include "model.h"
#include "latex/latexRenderThread.h"

#include "latex/latex.h"

std::string imageDir;



inline std::string toString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}



void initialiseLatex(const char *database, ModelSignaller *modelSignaller)
{
    imageDir = std::string(getpwuid(getuid())->pw_dir) + "/.StudyAidV3/" + database + "/";

    LatexRenderThread::initialise(modelSignaller, imageDir);
}

std::string getFactImageFilename(Fact fact)
{
    return imageDir + "/fact/" + toString(fact.id) + ".png";
}

std::string getProofImageFilename(Proof proof)
{
    return imageDir + "/proof/" + toString(proof.id) + ".png";
}

void renderFact(Fact fact)
{
    LatexRenderThread::getLatexRenderThread()->queueFact(fact);
}

void renderProof(Proof proof)
{
    LatexRenderThread::getLatexRenderThread()->queueProof(proof);
}

void recursivelyRenderFact(Fact fact)
{
    if (fact.type == "Section") {
        std::vector<Fact> facts = Database::findChildFacts(fact.id);
        for (size_t i = 0; i < facts.size(); i++) {
            recursivelyRenderFact(facts[i]);
        }
    }
    else {
        renderFact(fact);

        std::vector<Proof> proofs = Database::findProofsForFact(fact.id);
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

    std::vector<Course> courses = Database::findAllCourses();
    for (size_t i = 0; i < courses.size(); i++) {
        recursivelyRenderFact(Database::findFact(courses[i].root_fact));
    }
}