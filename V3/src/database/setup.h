#pragma once

#include <mysql++.h>

/* Initializes the connection
 */
void initialiseConnection(bool testMode);

/* Copies backup/restore scripts to user home
 * directory if not there already
 */
void initialiseBackup();

/* Clears the test database
 */
void clearTestDatabase();

/* Returns a connection to the database.
 */
mysqlpp::Connection *getConn();