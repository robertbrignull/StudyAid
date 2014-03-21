-- Remove the database if needed and add a new one
DROP DATABASE IF EXISTS study_aid_v3;
CREATE DATABASE study_aid_v3;
USE study_aid_v3;

-- Remove the user if needed and add a new one
GRANT USAGE ON *.* TO 'study_aid_v3'@'localhost'; -- a hack to create the user if they don't exist
DROP USER 'study_aid_v3'@'localhost';
CREATE USER 'study_aid_v3'@'localhost';
GRANT ALL PRIVILEGES ON study_aid_v3.* TO 'study_aid_v3'@'localhost';

-- Necessary to drop table, even though we have a new database
DROP TABLE IF EXISTS course;
DROP TABLE IF EXISTS proof_dependency;
DROP TABLE IF EXISTS fact_dependency;
DROP TABLE IF EXISTS proof;
DROP TABLE IF EXISTS fact;
DROP TABLE IF EXISTS fact_type;

-- Start creating tables
CREATE TABLE fact_type (
    fact_type VARCHAR(20) NOT NULL,
    fact_type_can_have_proof BOOLEAN NOT NULL,

    PRIMARY KEY fact_type_pkey (fact_type)
) engine=innodb;
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Section', FALSE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Axiom', FALSE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Definition', FALSE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Proposition', TRUE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Lemma', TRUE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Theorem', TRUE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Corollary', TRUE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Example', TRUE);
INSERT INTO fact_type (fact_type, fact_type_can_have_proof) VALUES ('Remark', TRUE);

CREATE TABLE fact (
    fact_id INTEGER NOT NULL AUTO_INCREMENT,
    fact_parent INTEGER,
    fact_name TEXT NOT NULL,
    fact_type VARCHAR(20) NOT NULL,
    fact_statement TEXT NOT NULL,
    fact_ordering INTEGER NOT NULL,

    PRIMARY KEY fact_id_pkey (fact_id),
    FOREIGN KEY fact_type_fkey (fact_type) REFERENCES fact_type (fact_type),
    FOREIGN KEY fact_parent_fkey (fact_parent) REFERENCES fact (fact_id)
) engine=innodb;

CREATE TABLE proof (
    proof_id INTEGER NOT NULL AUTO_INCREMENT,
    proof_fact INTEGER NOT NULL,
    proof_name TEXT NOT NULL,
    proof_body TEXT NOT NULL,
    proof_ordering INTEGER NOT NULL,

    PRIMARY KEY proof_id_pkey (proof_id),
    FOREIGN KEY proof_fact_fkey (proof_fact) REFERENCES fact (fact_id)
) engine=innodb;

CREATE TABLE fact_dependency (
    fact_dependency_dependency INTEGER NOT NULL,
    fact_dependency_depender INTEGER NOT NULL,

    PRIMARY KEY fact_dependency_pkey (fact_dependency_dependency, fact_dependency_depender),
    FOREIGN KEY fact_dependency_dependency_fkey (fact_dependency_dependency) REFERENCES fact (fact_id),
    FOREIGN KEY fact_dependency_depender_fkey (fact_dependency_depender) REFERENCES fact (fact_id)
) engine=innodb;

CREATE TABLE proof_dependency (
    proof_dependency_dependency INTEGER NOT NULL,
    proof_dependency_depender INTEGER NOT NULL,

    PRIMARY KEY proof_dependency_pkey (proof_dependency_dependency, proof_dependency_depender),
    FOREIGN KEY proof_dependency_dependency_fkey (proof_dependency_dependency) REFERENCES fact (fact_id),
    FOREIGN KEY proof_dependency_depender_fkey (proof_dependency_depender) REFERENCES proof (proof_id)
) engine=innodb;

CREATE TABLE course (
    course_id INTEGER NOT NULL AUTO_INCREMENT,
    course_name TEXT NOT NULL,
    course_ordering INTEGER NOT NULL,
    course_root_fact INTEGER NOT NULL,

    PRIMARY KEY course_id_pkey (course_id),
    FOREIGN KEY course_root_fact_fkey (course_root_fact) REFERENCES fact (fact_id)
) engine=innodb;