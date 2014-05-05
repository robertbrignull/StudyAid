#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
    remove(filename.c_str());
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

// Should return 0 on success, non 0 on error
int LatexRenderer::renderText(std::string text, std::string path, std::string filename)
{
    int status = 0;
    pid_t child_pid;

    std::string latex =
        std::string("\\documentclass[a4paper]{article}\n") +
        "\\usepackage{geometry}\n" +
        "\\usepackage[active,tightpage]{preview}\n" +
        "\\usepackage{dsfont}\n" +
        "\\usepackage{amsfonts}\n" +
        "\\usepackage{amsmath}\n" +
        "\\usepackage{amssymb}\n" +
        "\\usepackage{minted}\n" +
        "\\usepackage{tikz}\n" +
        "\\begin{document}\n" +
        "\\begin{preview}\n" +
        "\n" +
        text +
        "\n\n" +
        "\\end{preview}\n" +
        "\\end{document}";



    if (!writeToFile(latex, path + filename + ".latex")) {
        return 1;
    }

    

    ///////////////////////////////////
    // Fork the pdflatex process

    if ((child_pid = fork()) < 0)
    {
        perror("fork failure");
    }

    if (child_pid == 0) { // child process
        mkdir(path.c_str(), 0777);

        if (chdir(path.c_str()) == -1) {
            std::cerr << "    chdir failed" << std::endl;
            _exit(1);
        }

        execl("/usr/bin/pdflatex", "/usr/bin/pdflatex", "-shell-escape", "-halt-on-error", "-interaction=batchmode", "-output-directory", ".", (filename + ".latex").c_str(), NULL);
        std::cerr << "    Child process exec failed" << std::endl;
        _exit(1);
    }
    else {
        // parent process
        wait(&status);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            deleteFile(path + filename + ".pyg");
            deleteFile(path + filename + ".aux");
            deleteFile(path + filename + ".log");
            deleteFile(path + filename + ".pdf");

            return 1;
        }

        ///////////////////////////////////
        // Fork the pdftoppm process

        if ((child_pid = fork()) < 0)
        {
            perror("fork failure");
        }

        if (child_pid == 0) { // child process
            execl("/usr/bin/pdftoppm", "/usr/bin/pdftoppm", "-png", "-singlefile", "-r", "250", (path + filename + ".pdf").c_str(), (path + filename).c_str(), NULL);
            std::cerr << "    Child process exec failed" << std::endl;
            _exit(1);
        }
        else {
            // parent process
            wait(&status);

            deleteFile(path + filename + ".pyg");
            deleteFile(path + filename + ".aux");
            deleteFile(path + filename + ".log");
            deleteFile(path + filename + ".pdf");

            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}