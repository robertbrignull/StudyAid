#include "database/setup.h"

#include "database/methods.h"

Course loadCourse(mysqlpp::Row row)
{
    Course course;
    course.id = row["course_id"];
    course.name = std::string(row["course_name"]);
    course.ordering = row["course_ordering"];
    course.root_fact = row["course_root_fact"];
    return course;
}

Fact loadFact(mysqlpp::Row row)
{
    Fact fact;
    fact.id = row["fact_id"];
    fact.parent = row["fact_parent"];
    fact.name = std::string(row["fact_name"].c_str());
    fact.type = std::string(row["fact_type"].c_str());
    fact.statement = std::string(row["fact_statement"].c_str());
    fact.ordering = row["fact_ordering"];
    return fact;
}

int addCourse(std::string name)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);
    mysqlpp::SimpleResult result;

    query << "INSERT INTO fact (fact_parent, fact_name, fact_type, fact_statement, fact_ordering) VALUES (NULL, '', 'Section', '', 0)";
    result = query.execute();

    int root_fact_id = result.insert_id();

    query.reset();
    query << "SELECT MAX(course_ordering) AS ordering FROM course";
    mysqlpp::StoreQueryResult storeResult = query.store();

    int ordering = 0;
    if (storeResult[0]["ordering"] != mysqlpp::null) {
        ordering = storeResult[0]["ordering"] + 1;
    }

    query.reset();
    query << "INSERT INTO course (course_name, course_ordering, course_root_fact) VALUES (%0q, %1q, %2q)";
    query.parse();
    result = query.execute(name, ordering, root_fact_id);

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

    return loadCourse(result[0]);
}

std::vector<Course> findAllCourses()
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM course");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store();

    std::vector<Course> courses;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        courses.push_back(loadCourse(result[i]));
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
    mysqlpp::Query query(conn, true);

    query << "SELECT MAX(fact_ordering) AS ordering FROM fact WHERE fact_parent = %0q";
    query.parse();
    mysqlpp::StoreQueryResult storeResult = query.store(parent);

    int ordering = 0;
    if (storeResult[0]["ordering"] != mysqlpp::null) {
        ordering = storeResult[0]["ordering"] + 1;
    }

    query.reset();
    query << "INSERT INTO fact (fact_parent, fact_name, fact_type, fact_statement, fact_ordering) VALUES (%0q, %1q, %2q, '', %3q)";
    query.parse();

    return query.execute(parent, name, type, ordering).insert_id();
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

    return loadFact(result[0]);
}

std::vector<Fact> findChildSections(int parent)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM fact WHERE fact_parent = %0q AND fact_type = 'Section'");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(parent);

    std::vector<Fact> facts;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        facts.push_back(loadFact(result[i]));
    }

    return facts;
}

std::vector<Fact> findChildFacts(int parent)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM fact WHERE fact_parent = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(parent);

    std::vector<Fact> facts;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        facts.push_back(loadFact(result[i]));
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