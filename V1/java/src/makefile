targetDir := ../target
srcDir := ${targetDir}/src
classDir := ${targetDir}/class
jarDir := ${targetDir}/jar
libDir := ../lib
databaseDir := ../../database
webappDir := ../../webapps

package : run
	javac ${srcDir}/StudyAid/StudyAid.java -d ${classDir}
	javac ${srcDir}/StudyAid/Tables/*.java -d ${classDir}
	jar cf ${jarDir}/StudyAid.jar -C ${classDir} StudyAid
	cp ${jarDir}/StudyAid.jar ${webappDir}/WEB-INF/lib/StudyAid.jar

run : build ${databaseDir}/setupDatabase.sql
	mkdir -p ${srcDir}
	java -jar ${jarDir}/Scaffold.jar localhost 3306 root mysql StudyAid ${srcDir}

build : Scaffold.jar

Scaffold.jar : ${classDir}/Scaffold/DBConnection.class ${classDir}/Scaffold/Scaffold.class ${classDir}/Scaffold/TypeInfo.class ${classDir}/Scaffold/Routine/Parameter.class ${classDir}/Scaffold/Routine/Routine.class ${classDir}/Scaffold/Table/Column.class ${classDir}/Scaffold/Table/ForeignKeyReference.class ${classDir}/Scaffold/Table/Table.class ${classDir}/Scaffold/SQLServer/SQLServerConnection.class ${classDir}/Scaffold/SQLServer/ScalarFunction.class ${classDir}/Scaffold/SQLServer/StoredProcedure.class ${classDir}/Scaffold/SQLServer/TableFunction.class ${classDir}/Scaffold/MySQL/MySQLConnection.class
	rm -rf tmp
	mkdir tmp
	cd tmp; jar xf ../${libDir}/*.jar
	mkdir -p ${jarDir}
	jar cmf manifest.mf ${jarDir}/Scaffold.jar -C ${classDir} . -C tmp .
	rm -rf tmp

${classDir}/Scaffold/DBConnection.class : Scaffold/DBConnection.java Scaffold/Routine/Routine.java Scaffold/Table/Table.java
	mkdir -p ${classDir}/Scaffold
	javac Scaffold/DBConnection.java -d ${classDir}

${classDir}/Scaffold/Scaffold.class : Scaffold/Scaffold.java Scaffold/Routine/Routine.java Scaffold/Table/Table.java Scaffold/SQLServer/SQLServerConnection.java Scaffold/TypeInfo.java Scaffold/DBConnection.java Scaffold/MySQL/MySQLConnection.java
	mkdir -p ${classDir}/Scaffold
	javac Scaffold/Scaffold.java -d ${classDir}

${classDir}/Scaffold/TypeInfo.class : Scaffold/TypeInfo.java
	mkdir -p ${classDir}/Scaffold
	javac Scaffold/TypeInfo.java -d ${classDir}

${classDir}/Scaffold/Routine/Parameter.class : Scaffold/Routine/Parameter.java Scaffold/TypeInfo.java
	mkdir -p ${classDir}/Scaffold/Routine
	javac Scaffold/Routine/Parameter.java -d ${classDir}

${classDir}/Scaffold/Routine/Routine.class : Scaffold/Routine/Routine.java Scaffold/Routine/Parameter.java
	mkdir -p ${classDir}/Scaffold/Routine
	javac Scaffold/Routine/Routine.java -d ${classDir}

${classDir}/Scaffold/Table/Column.class : Scaffold/Table/Column.java Scaffold/TypeInfo.java Scaffold/Table/ForeignKeyReference.java
	mkdir -p ${classDir}/Scaffold/Table
	javac Scaffold/Table/Column.java -d ${classDir}

${classDir}/Scaffold/Table/ForeignKeyReference.class : Scaffold/Table/ForeignKeyReference.java Scaffold/Scaffold.java
	mkdir -p ${classDir}/Scaffold/Table
	javac Scaffold/Table/ForeignKeyReference.java -d ${classDir}

${classDir}/Scaffold/Table/Table.class : Scaffold/Table/Table.java Scaffold/Scaffold.java Scaffold/Table/Column.java Scaffold/Table/ForeignKeyReference.java
	mkdir -p ${classDir}/Scaffold/Table
	javac Scaffold/Table/Table.java -d ${classDir}

${classDir}/Scaffold/SQLServer/SQLServerConnection.class : Scaffold/SQLServer/SQLServerConnection.java Scaffold/DBConnection.java Scaffold/TypeInfo.java Scaffold/Routine/Parameter.java Scaffold/Routine/Routine.java Scaffold/Table/Column.java Scaffold/Table/ForeignKeyReference.java Scaffold/Table/Table.java Scaffold/SQLServer/ScalarFunction.java Scaffold/SQLServer/StoredProcedure.java Scaffold/SQLServer/TableFunction.java
	mkdir -p ${classDir}/Scaffold/SQLServer
	javac Scaffold/SQLServer/SQLServerConnection.java -d ${classDir}

${classDir}/Scaffold/SQLServer/ScalarFunction.class : Scaffold/SQLServer/ScalarFunction.java Scaffold/Scaffold.java Scaffold/TypeInfo.java Scaffold/Routine/Parameter.java Scaffold/Routine/Routine.java
	mkdir -p ${classDir}/Scaffold/SQLServer
	javac Scaffold/SQLServer/ScalarFunction.java -d ${classDir}

${classDir}/Scaffold/SQLServer/StoredProcedure.class : Scaffold/SQLServer/StoredProcedure.java Scaffold/Scaffold.java Scaffold/Routine/Parameter.java Scaffold/Routine/Routine.java
	mkdir -p ${classDir}/Scaffold/SQLServer
	javac Scaffold/SQLServer/StoredProcedure.java -d ${classDir}

${classDir}/Scaffold/SQLServer/TableFunction.class : Scaffold/SQLServer/TableFunction.java Scaffold/Scaffold.java Scaffold/Routine/Parameter.java Scaffold/Routine/Routine.java
	mkdir -p ${classDir}/Scaffold/SQLServer
	javac Scaffold/SQLServer/TableFunction.java -d ${classDir}

${classDir}/Scaffold/MySQL/MySQLConnection.class : Scaffold/MySQL/MySQLConnection.java Scaffold/DBConnection.java Scaffold/TypeInfo.java Scaffold/Routine/Parameter.java Scaffold/Routine/Routine.java Scaffold/Table/Column.java Scaffold/Table/ForeignKeyReference.java Scaffold/Table/Table.java
	mkdir -p ${classDir}/Scaffold/MySQL
	javac Scaffold/MySQL/MySQLConnection.java -d ${classDir}

clean :
	rm -rf ${targetDir}
