#pragma once

#include <mysql++.h>

/* Checks that MySQL is installed and the StudyAid database exists.
 * Returns true if connected successfully, else returns false.
 */
bool connectToDatabase();

/* Returns a connection to the database.
 */
mysqlpp::Connection *getConn();