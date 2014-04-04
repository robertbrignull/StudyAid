
-- Remove the databases if needed and add new ones
DROP DATABASE IF EXISTS study_aid_v3;
DROP DATABASE IF EXISTS study_aid_v3_test;

CREATE DATABASE study_aid_v3;
CREATE DATABASE study_aid_v3_test;

-- Remove the user if needed and add a new one
GRANT USAGE ON *.* TO 'study_aid_v3'@'localhost'; -- a hack to create the user if they don't exist
DROP USER 'study_aid_v3'@'localhost';
CREATE USER 'study_aid_v3'@'localhost';
GRANT ALL PRIVILEGES ON study_aid_v3.* TO 'study_aid_v3'@'localhost';
GRANT ALL PRIVILEGES ON study_aid_v3_test.* TO 'study_aid_v3'@'localhost';
