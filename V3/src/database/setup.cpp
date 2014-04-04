#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <errno.h>

#include <iostream>

#include <mysql++.h>

#include <QFile>
#include <QString>
#include <QTextStream>

#include "database/setup.h"

std::string databaseName = "study_aid_v3";
std::string server = "127.0.0.1";
std::string user = "study_aid_v3";
std::string password = "";

mysqlpp::Connection conn = mysqlpp::Connection(true);

void initialiseConnection(bool testMode)
{
    if (testMode) {
        databaseName = "study_aid_v3_test";
    }
}

void initialiseBackup()
{
    struct passwd *pw = getpwuid(getuid());

    std::string dataDir = std::string(pw->pw_dir) + "/.StudyAidV3/";



    // Only copy things if the directory did not exist
    if (mkdir((dataDir + "database").c_str(), 0777) == 0) {
        QFile::copy(":/database/backup", QString::fromStdString(dataDir + "database/backup"));
        QFile::copy(":/database/restore", QString::fromStdString(dataDir + "database/restore"));
        QFile::copy(":/database/install", QString::fromStdString(dataDir + "database/install"));
        QFile::copy(":/database/installDatabases.sql", QString::fromStdString(dataDir + "database/installDatabases.sql"));
        QFile::copy(":/database/setupDatabase.sql", QString::fromStdString(dataDir + "database/setupDatabase.sql"));

        QFile::setPermissions(QString::fromStdString(dataDir + "database/backup"), QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner | QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup | QFile::ReadOther);
        QFile::setPermissions(QString::fromStdString(dataDir + "database/restore"), QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner | QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup | QFile::ReadOther);
        QFile::setPermissions(QString::fromStdString(dataDir + "database/install"), QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner | QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup | QFile::ReadOther);
    }
}

void clearTestDatabase()
{
    if (databaseName != "study_aid_v3_test") return;

    mysqlpp::Query(getConn(), true, "DELETE FROM course").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM proof_dependency").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM fact_dependency").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM proof").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM fact").execute();
}

mysqlpp::Connection *getConn()
{
    if (!conn.connected()) {
        conn.connect(databaseName.c_str(), server.c_str(), user.c_str(), password.c_str(), 0);
    }

    return &conn;
}