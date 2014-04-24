#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <errno.h>

#include <mysql++.h>

#include <libxml++/libxml++.h>

#include <QFile>
#include <QString>
#include <QTextStream>

#include "database/setup.h"

std::string databaseName;
std::string server;
std::string user;
std::string password;

mysqlpp::Connection conn = mysqlpp::Connection(true);

std::string extractValue(xmlpp::Element *root_node, const char *name)
{
    auto nodeList = root_node->find(name);

    if (nodeList.size() != 1) {
        std::cerr << "Could not parse config file, nodeList incorrect length" << std::endl;
        exit(1);
    }

    auto node = *nodeList.begin();

    if (!dynamic_cast<xmlpp::Element*>(node)) {
        std::cerr << "Could not parse config file, node not an element" << std::endl;
        exit(1);
    }

    auto element = dynamic_cast<xmlpp::Element*>(node);

    if (!element->get_child_text()) {
        return "";
    }
    else {
        return element->get_child_text()->get_content();
    }
}

void initialiseConnection(const char *database)
{
    std::string configFilename = std::string(getpwuid(getuid())->pw_dir) + "/.StudyAidV3/database/config.xml";

    xmlpp::DomParser parser(configFilename);

    if (parser.get_document() == 0) {
        std::cerr << "Config file ~/.StudyAidV3/database/config.xml not found" << std::endl;
        exit(1);
    }

    xmlpp::Node *root_node = parser.get_document()->get_root_node();

    auto children = root_node->get_children(database);
    if (children.size() != 1) {
        std::cerr << "Could not parse config file, database not recognized" << std::endl;
        exit(1);
    }
    
    xmlpp::Element *config = dynamic_cast<xmlpp::Element*>(*children.begin());

    databaseName = extractValue(config, "databaseName");
    server = extractValue(config, "server");
    user = extractValue(config, "user");
    password = extractValue(config, "password");

    conn.connect(databaseName.c_str(), server.c_str(), user.c_str(), password.c_str(), 0);
}

void initialiseBackup()
{
    std::string dataDir = std::string(getpwuid(getuid())->pw_dir) + "/.StudyAidV3/";



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

    mysqlpp::Query(getConn(), true, "SET FOREIGN_KEY_CHECKS = 0").execute();

    mysqlpp::Query(getConn(), true, "DELETE FROM course").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM proof_dependency").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM fact_dependency").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM proof").execute();
    mysqlpp::Query(getConn(), true, "DELETE FROM fact").execute();
    
    mysqlpp::Query(getConn(), true, "SET FOREIGN_KEY_CHECKS = 1;").execute();
}

mysqlpp::Connection *getConn()
{
    if (!conn.ping()) {
        std::cout << "ping failed" << std::endl;
    }

    return &conn;
}