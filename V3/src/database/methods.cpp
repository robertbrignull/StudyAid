#include "database/setup.h"

#include "database/methods.h"

int addCourse(std::string name)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);
    mysqlpp::SimpleResult result;

    query << "INSERT INTO fact (fact_parent, fact_name, fact_type, fact_statement, fact_ordering) VALUES (NULL, '', 'Section', '', 0)";
    result = query.execute();

    int root_fact_id = result.insert_id();

    query.reset();
    query << "INSERT INTO course (course_name, course_ordering, course_root_fact) VALUES (%0q:name, (SELECT MAX(course_ordering)+1 FROM course), %1q:root_fact)";
    query.parse();
    result = query.execute(name, root_fact_id);

    return result.insert_id();
}

Course findCourse(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM course WHERE course_id = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(id);

    if (result.num_rows() != 1) {
        throw new NotFoundException();
    }

    Course course;
    course.id = id;
    course.name = std::string(result[0]["course_name"]);
    course.ordering = result[0]["course_ordering"];
    course.root_fact = result[0]["course_root_fact"];

    return course;
}

std::vector<Course> findAllCourses()
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM course");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store();

    std::vector<Course> courses;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        Course course;
        course.id = result[i]["course_id"];
        course.name = std::string(result[i]["course_name"]);
        course.ordering = result[i]["course_ordering"];
        course.root_fact = result[i]["course_root_fact"];

        courses.push_back(course);
    }

    return courses;
}

void editCourse(Course course)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "UPDATE course SET course_name = %0q, course_ordering = %1q, course_root_fact = %2q WHERE course_id = %3q");
    query.parse();

    query.execute(course.name, course.ordering, course.root_fact, course.id);
}

void deleteCourse(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "DELETE FROM course WHERE course_id = %0q");
    query.parse();

    query.execute(id);
}

int addFact(int parent, std::string name, FactType type)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "INSERT INTO fact (fact_parent, fact_name, fact_type, fact_statement, fact_ordering) VALUES (%0q, %1q, %2q, '', (SELECT MAX(fact_ordering)+1 FROM fact WHERE fact_parent = %0q))");
    query.parse();

    mysqlpp::SimpleResult result = query.execute(parent, name, type);

    return result.insert_id();
}

Fact findFact(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM fact WHERE fact_id = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(id);

    if (result.num_rows() != 1) {
        throw new NotFoundException();
    }

    Fact fact;
    fact.id = id;
    fact.parent = result[0]["fact_parent"];
    fact.name = std::string(result[0]["fact_name"].c_str());
    fact.type = std::string(result[0]["fact_type"].c_str());
    fact.statement = std::string(result[0]["fact_statement"].c_str());
    fact.ordering = result[0]["fact_ordering"];

    return fact;
}

std::vector<Fact> findChildFacts(int parent)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM fact WHERE fact_parent = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(parent);

    std::vector<Fact> facts;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        Fact fact;
        fact.id = result[i]["fact_id"];
        fact.parent = result[i]["fact_parent"];
        fact.name = std::string(result[i]["fact_name"].c_str());
        fact.type = std::string(result[i]["fact_type"].c_str());
        fact.statement = std::string(result[i]["fact_statement"].c_str());
        fact.ordering = result[i]["fact_ordering"];

        facts.push_back(fact);
    }

    return facts;
}

void editFact(Fact fact)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "UPDATE fact SET fact_parent = %0q, fact_name = %1q, fact_type = %2q, fact_statement = %3q, fact_ordering = %4q WHERE fact_id = %5q");
    query.parse();

    query.execute(fact.parent, fact.name, fact.type, fact.statement, fact.ordering, fact.id);
}

void deleteFact(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "DELETE FROM fact WHERE fact_id = %0q");
    query.parse();

    query.execute(id);
}