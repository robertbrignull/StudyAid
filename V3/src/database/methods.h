#pragma once

#include <iostream>
#include <vector>

#include "database/structures.h"

namespace Database
{
    int addCourse(std::string name);
    Course findCourse(int id);
    std::vector<Course> findAllCourses();
    Course findCourseByRootFact(int id);
    void editCourse(Course course);
    void editCourseOrdering(Course course);
    void deleteCourse(int id);

    int addFact(int parent, std::string name, std::string type);
    Fact findFact(int id);
    std::vector<Fact> findChildSections(int parent);
    std::vector<Fact> findChildFacts(int parent);
    void editFact(Fact fact);
    void editFactOrdering(Fact fact);
    void deleteFact(int id);

    FactType findFactType(std::string factType);
    std::vector<FactType> findAllFactTypes();

    int addProof(int fact, std::string name);
    Proof findProof(int id);
    std::vector<Proof> findProofsForFact(int fact);
    void editProof(Proof proof);
    void editProofOrdering(Proof proof);
    void deleteProof(int id);
}