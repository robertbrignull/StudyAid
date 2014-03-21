#include <iostream>

#include <mysql++.h>

#include "database/setup.h"

const char *databaseName = "study_aid_v3";
const char *server = "127.0.0.1";
const char *user = "study_aid_v3";
const char *password = "";

mysqlpp::Connection conn;

bool connectToDatabase() {
    conn = mysqlpp::Connection(true);

    try {
        conn.connect(databaseName, server, user, password, 0);
    }
    catch (mysqlpp::ConnectionFailed ex) {
        std::cout << "Could not connect to database: " << conn.error() << std::endl;
        return false;
    }

    return true;
}

mysqlpp::Connection getConn() {
    return conn;
}