#include "database/setup.h"

#include "database/methods.h"

int addCourse(std::string name)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);
    mysqlpp::SimpleResult result;

    query << "INSERT INTO fact (fact_parent, fact_name, fact_type, fact_statement, fact_ordering) VALUES (NULL, '', Section, '', 0)";
    result = query.execute();

    int root_fact_id = result.insert_id();

    query.reset();
    query << "INSERT INTO course (course_name, course_ordering, course_root_fact) VALUES (%0:name, 0, %2:root_fact)";
    query.parse();
    result = query.execute(name, root_fact_id);

    return result.insert_id();
}

Course findCourse(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM course WHERE id = %0");
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

    mysqlpp::Query query(conn, true, "UPDATE course SET course_name = %0, course_ordering = %1, course_root_fact = %2 WHERE course_id = %3");
    query.parse();

    query.execute(course.name, course.ordering, course.root_fact, course.id);
}

void deleteCourse(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "DELETE FROM course WHERE id = %0");
    query.parse();

    query.execute(id);
}