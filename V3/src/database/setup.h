#pragma once

/* Checks that MySQL is installed, then checks if the StudyAid database exists,
 * if not then initializes database.
 * Returns true if the database is setup correctly, else returns false.
 */
bool setupDatabase();