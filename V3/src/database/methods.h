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