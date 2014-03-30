#pragma once

#include <mysql++.h>

/* Initializes the connection
 */
void initialiseDatabase(bool testMode);

/* Returns a connection to the database.
 */
mysqlpp::Connection *getConn();