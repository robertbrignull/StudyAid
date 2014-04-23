#pragma once

#include <iostream>

#include "database/structures.h"

class ModelSignaller;

void initialiseLatex(const char *database, ModelSignaller *modelSignaller);

/* Return the path to the file where this fact or
 * proof's rendered image should be stored.
 */
std::string getFactImageFilename(Fact fact);
std::string getProofImageFilename(Proof proof);

/* Queues a fact/proof for rendering
 */
void renderFact(Fact fact);
void renderProof(Proof proof);

/* Removes all rendered images and renders
 * everything from scratch.
 */
void renderAll();