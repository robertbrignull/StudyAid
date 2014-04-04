#pragma once

#include <iostream>
#include <vector>

#include "database/structures.h"



/* Adds a new course and returns its id.
 */
int addCourse(std::string name);

/* Returns the course with the given id.
 */
Course findCourse(int id);

/* Returns all courses.
 */
std::vector<Course> findAllCourses();

/* Updates the course with the id in the struct
 * with the other values from the struct.
 */
void editCourse(Course course);

/* Deletes the course with the given id.
 */
void deleteCourse(int id);



/* Adds a new fact and returns its id.
 */
int addFact(int parent, std::string name, std::string type);

/* Returns the fact with the given id.
 */
Fact findFact(int id);

/* Returns all the children of a given parent fact which are sections.
 */
std::vector<Fact> findChildSections(int parent);

/* Returns all the children of a given parent fact.
 */
std::vector<Fact> findChildFacts(int parent);

/* Updates the fact with the id in the struct
 * with the other values from the struct.
 */
void editFact(Fact fact);

/* Deletes the fact with the given id.
 */
void deleteFact(int id);



/* Returns a fact type by its name
 */
FactType findFactType(std::string factType);

/* Returns all fact types.
 */
std::vector<FactType> findAllFactTypes();



/* Adds a new proof and returns its id.
 */
int addProof(int fact, std::string name);

/* Returns the proof with the given id.
 */
Proof findProof(int id);

/* Returns all the children of a given parent proof.
 */
std::vector<Proof> findProofsForFact(int fact);

/* Updates the proof with the id in the struct
 * with the other values from the struct.
 */
void editProof(Proof proof);

/* Deletes the proof with the given id.
 */
void deleteProof(int id);