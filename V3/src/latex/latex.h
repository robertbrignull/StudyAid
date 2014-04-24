#pragma once

#include <iostream>

#include "database/structures.h"

class ModelSignaller;

void initialiseLatex(const char *database);

/* Return the path to the file where this fact or
 * proof's rendered image should be stored.
 */
std::string getImageDir();
std::string getFactImageFilename(Fact fact);
std::string getProofImageFilename(Proof proof);

/* Removes all rendered images and renders
 * everything from scratch.
 */
void renderAll();