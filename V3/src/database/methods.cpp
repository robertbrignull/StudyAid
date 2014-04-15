#include "database/setup.h"

#include "database/methods.h"

//  ##       #####     ##    #####   ###### ##    ##  #####
//  ##      ##   ##   ####   ##  ###   ##   ###   ## ##   ##
//  ##      ##   ##  ##  ##  ##   ##   ##   ####  ## ##
//  ##      ##   ## ##    ## ##   ##   ##   ## ## ## ##  ###
//  ##      ##   ## ######## ##   ##   ##   ##  #### ##   ##
//  ##      ##   ## ##    ## ##  ###   ##   ##   ### ##   ##
//  #######  #####  ##    ## #####   ###### ##    ##  #####

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
    fact.parent = (row["fact_parent"] != mysqlpp::null) ? row["fact_parent"] : -1;
    fact.name = std::string(row["fact_name"].c_str());
    fact.type = std::string(row["fact_type"].c_str());
    fact.statement = std::string(row["fact_statement"].c_str());
    fact.ordering = row["fact_ordering"];
    return fact;
}

FactType loadFactType(mysqlpp::Row row)
{
    FactType factType;
    factType.fact_type = std::string(row["fact_type"].c_str());
    factType.can_have_proof = row["fact_type_can_have_proof"];
    factType.colour = std::string(row["fact_type_colour"].c_str());
    return factType;
}

Proof loadProof(mysqlpp::Row row)
{
    Proof proof;
    proof.id = row["proof_id"];
    proof.fact = row["proof_fact"];
    proof.name = std::string(row["proof_name"].c_str());
    proof.body = std::string(row["proof_body"].c_str());
    proof.ordering = row["proof_ordering"];
    return proof;
}

//   #####   #####  ##   ## ######   #####  #######
//  ##   ## ##   ## ##   ## ##   ## ##   ## ##
//  ##      ##   ## ##   ## ##   ##  ##     ##
//  ##      ##   ## ##   ## ##  ###   ###   #####
//  ##      ##   ## ##   ## #####       ##  ##
//  ##   ## ##   ## ##   ## ##  ##  ##   ## ##
//   #####   #####   #####  ##   ##  #####  #######

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

    mysqlpp::Query query(conn, true, "UPDATE course SET course_name = %0q WHERE course_id = %1q");
    query.parse();

    query.execute(course.name, course.id);
}

void editCourseOrdering(Course course)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);

    query << "UPDATE course SET course_ordering = course_ordering + 1 WHERE course_ordering >= %0q";
    query.parse();
    query.execute(course.ordering);

    query.reset();
    query << "UPDATE course SET course_ordering = %0q WHERE course_id = %1q";
    query.parse();
    query.execute(course.ordering, course.id);
}

void deleteCourse(int id)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);

    query << "SELECT course_root_fact FROM course WHERE course_id = %0q";
    query.parse();
    mysqlpp::StoreQueryResult storeResult = query.store(id);

    query.reset();
    query << "DELETE FROM course WHERE course_id = %0q";
    query.parse();
    query.execute(id);

    query.reset();
    query << "DELETE FROM fact WHERE fact_id = %0q";
    query.parse();
    query.execute(storeResult[0]["course_root_fact"]);
}

//  #######    ##     #####  ########
//  ##        ####   ##   ##    ##
//  ##       ##  ##  ##         ##
//  #####   ##    ## ##         ##
//  ##      ######## ##         ##
//  ##      ##    ## ##   ##    ##
//  ##      ##    ##  #####     ##

int addFact(int parent, std::string name, std::string type)
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

    mysqlpp::Query query(conn, true, "UPDATE fact SET fact_name = %0q, fact_type = %1q, fact_statement = %2q WHERE fact_id = %3q");
    query.parse();

    query.execute(fact.name, fact.type, fact.statement, fact.id);
}

void editFactOrdering(Fact fact)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);

    query << "UPDATE fact SET fact_ordering = fact_ordering + 1 WHERE fact_parent = %0q AND fact_ordering >= %1q";
    query.parse();
    query.execute(fact.parent, fact.ordering);

    query.reset();
    query << "UPDATE fact SET fact_parent = %0q, fact_ordering = %1q WHERE fact_id = %2q";
    query.parse();
    query.execute(fact.parent, fact.ordering, fact.id);
}

void deleteFact(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "DELETE FROM fact WHERE fact_id = %0q");
    query.parse();

    query.execute(id);
}

//  #######    ##     #####  ########         ######## ##    ## ######  #######
//  ##        ####   ##   ##    ##               ##     ##  ##  ##   ## ##
//  ##       ##  ##  ##         ##               ##      ####   ##   ## ##
//  #####   ##    ## ##         ##               ##       ##    ######  #####
//  ##      ######## ##         ##               ##       ##    ##      ##
//  ##      ##    ## ##   ##    ##               ##       ##    ##      ##
//  ##      ##    ##  #####     ##               ##       ##    ##      #######

FactType findFactType(std::string factType)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM fact_type WHERE fact_type = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(factType);

    if (result.num_rows() != 1) {
        throw new NotFoundException();
    }

    return loadFactType(result[0]);
}

std::vector<FactType> findAllFactTypes()
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM fact_type");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store();

    std::vector<FactType> factTypes;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        factTypes.push_back(loadFactType(result[i]));
    }

    return factTypes;
}



//  ######  ######   #####   #####  #######
//  ##   ## ##   ## ##   ## ##   ## ##
//  ##   ## ##   ## ##   ## ##   ## ##
//  ######  ######  ##   ## ##   ## #####
//  ##      ##  ##  ##   ## ##   ## ##
//  ##      ##   ## ##   ## ##   ## ##
//  ##      ##    #  #####   #####  ##

int addProof(int fact, std::string name)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);

    query << "SELECT MAX(proof_ordering) AS ordering FROM proof WHERE proof_fact = %0q";
    query.parse();
    mysqlpp::StoreQueryResult storeResult = query.store(fact);

    int ordering = 0;
    if (storeResult[0]["ordering"] != mysqlpp::null) {
        ordering = storeResult[0]["ordering"] + 1;
    }

    query.reset();
    query << "INSERT INTO proof (proof_fact, proof_name, proof_body, proof_ordering) VALUES (%0q, %1q, '', %2q)";
    query.parse();

    return query.execute(fact, name, ordering).insert_id();
}

Proof findProof(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM proof WHERE proof_id = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(id);

    if (result.num_rows() != 1) {
        throw new NotFoundException();
    }

    return loadProof(result[0]);
}

std::vector<Proof> findProofsForFact(int fact)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "SELECT * FROM proof WHERE proof_fact = %0q");
    query.parse();

    mysqlpp::StoreQueryResult result = query.store(fact);

    std::vector<Proof> proofs;

    for (size_t i = 0; i < result.num_rows(); ++i) {
        proofs.push_back(loadProof(result[i]));
    }

    return proofs;
}

void editProof(Proof proof)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "UPDATE proof SET proof_name = %0q, proof_body = %1q WHERE proof_id = %2q");
    query.parse();

    query.execute(proof.name, proof.body, proof.id);
}

void editProofOrdering(Proof proof)
{
    mysqlpp::Connection *conn = getConn();
    mysqlpp::Query query(conn, true);

    query << "UPDATE proof SET proof_ordering = proof_ordering + 1 WHERE proof_fact = %0q AND proof_ordering >= %1q";
    query.parse();
    query.execute(proof.fact, proof.ordering);

    query.reset();
    query << "UPDATE proof SET proof_ordering = %0q WHERE proof_id = %1q";
    query.parse();
    query.execute(proof.ordering, proof.id);
}

void deleteProof(int id)
{
    mysqlpp::Connection *conn = getConn();

    mysqlpp::Query query(conn, true, "DELETE FROM proof WHERE proof_id = %0q");
    query.parse();

    query.execute(id);
}