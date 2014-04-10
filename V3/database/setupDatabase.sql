
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
    fact_type_colour VARCHAR(6) NOT NULL,

    PRIMARY KEY fact_type_pkey (fact_type)
) engine=innodb;
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Section', FALSE, "000000");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Axiom', FALSE, "45A145");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Definition', FALSE, "5555A3");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Proposition', TRUE, "996E00");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Lemma', TRUE, "929900");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Theorem', TRUE, "990000");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Corollary', TRUE, "1A5C00");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Example', TRUE, "49C4C4");
INSERT INTO fact_type (fact_type, fact_type_can_have_proof, fact_type_colour) VALUES ('Remark', TRUE, "009987");

CREATE TABLE fact (
    fact_id INTEGER NOT NULL AUTO_INCREMENT,
    fact_parent INTEGER,
    fact_name TEXT NOT NULL,
    fact_type VARCHAR(20) NOT NULL,
    fact_statement TEXT NOT NULL,
    fact_ordering INTEGER NOT NULL,

    PRIMARY KEY fact_id_pkey (fact_id),
    FOREIGN KEY fact_type_fkey (fact_type) REFERENCES fact_type (fact_type),
    FOREIGN KEY fact_parent_fkey (fact_parent) REFERENCES fact (fact_id) ON DELETE CASCADE
) engine=innodb;

CREATE TABLE proof (
    proof_id INTEGER NOT NULL AUTO_INCREMENT,
    proof_fact INTEGER NOT NULL,
    proof_name TEXT NOT NULL,
    proof_body TEXT NOT NULL,
    proof_ordering INTEGER NOT NULL,

    PRIMARY KEY proof_id_pkey (proof_id),
    FOREIGN KEY proof_fact_fkey (proof_fact) REFERENCES fact (fact_id) ON DELETE CASCADE
) engine=innodb;

CREATE TABLE fact_dependency (
    fact_dependency_dependency INTEGER NOT NULL,
    fact_dependency_depender INTEGER NOT NULL,

    PRIMARY KEY fact_dependency_pkey (fact_dependency_dependency, fact_dependency_depender),
    FOREIGN KEY fact_dependency_dependency_fkey (fact_dependency_dependency) REFERENCES fact (fact_id) ON DELETE CASCADE,
    FOREIGN KEY fact_dependency_depender_fkey (fact_dependency_depender) REFERENCES fact (fact_id) ON DELETE CASCADE
) engine=innodb;

CREATE TABLE proof_dependency (
    proof_dependency_dependency INTEGER NOT NULL,
    proof_dependency_depender INTEGER NOT NULL,

    PRIMARY KEY proof_dependency_pkey (proof_dependency_dependency, proof_dependency_depender),
    FOREIGN KEY proof_dependency_dependency_fkey (proof_dependency_dependency) REFERENCES fact (fact_id) ON DELETE CASCADE,
    FOREIGN KEY proof_dependency_depender_fkey (proof_dependency_depender) REFERENCES proof (proof_id) ON DELETE CASCADE
) engine=innodb;

CREATE TABLE course (
    course_id INTEGER NOT NULL AUTO_INCREMENT,
    course_name TEXT NOT NULL,
    course_ordering INTEGER NOT NULL,
    course_root_fact INTEGER NOT NULL,

    PRIMARY KEY course_id_pkey (course_id),
    FOREIGN KEY course_root_fact_fkey (course_root_fact) REFERENCES fact (fact_id)
) engine=innodb;
