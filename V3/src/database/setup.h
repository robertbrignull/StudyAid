#pragma once

#include <mysql++.h>

/* Returns a connection to the database.
 */
mysqlpp::Connection *getConn();