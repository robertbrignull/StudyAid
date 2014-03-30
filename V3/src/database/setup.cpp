#include <iostream>

#include <mysql++.h>

#include "database/setup.h"

const char *databaseName = "study_aid_v3";
const char *server = "127.0.0.1";
const char *user = "study_aid_v3";
const char *password = "";

mysqlpp::Connection conn = mysqlpp::Connection(true);

mysqlpp::Connection *getConn() {
    if (!conn.connected()) {
        conn.connect(databaseName, server, user, password, 0);
    }

    return &conn;
}