#pragma once

#include <iostream>

#include "database/structures.h"

void initialiseLatex();

/* Return the path to the file where this fact or
 * proof's rendered image should be stored.
 */
std::string getFactImageFilename(Fact fact);
std::string getProofImageFilename(Proof proof);

/* Renders a fact or proof.
 * Returns 0 on success.
 *         1 if the latex is invalid
 *         2 if there was a more serious error
 */
int renderFact(Fact fact);
int renderProof(Proof proof);