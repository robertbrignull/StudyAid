#include <iostream>

#include <mysql++.h>

#include "database/setup.h"

std::string databaseName = "study_aid_v3";
std::string server = "127.0.0.1";
std::string user = "study_aid_v3";
std::string password = "";

mysqlpp::Connection conn = mysqlpp::Connection(true);

void initialiseDatabase(bool testMode)
{
    if (testMode) {
        databaseName = "study_aid_v3_test";
    }
}

mysqlpp::Connection *getConn()
{
    if (!conn.connected()) {
        conn.connect(databaseName.c_str(), server.c_str(), user.c_str(), password.c_str(), 0);
    }

    return &conn;
}