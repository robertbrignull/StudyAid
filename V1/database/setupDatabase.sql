drop database if exists StudyAid;
create database StudyAid;
use StudyAid;

drop table if exists Dependency;
drop table if exists Proof;
drop table if exists Fact;
drop table if exists FactType;
drop table if exists Course;

create table Course
(
	courseID integer not null auto_increment,
	courseName varchar(100) not null,

	primary key courseIDPKey (courseID)
) engine=innodb;

create table FactType
(
	factType varchar(20) not null,
	factTypeColour varchar(6) not null,
	factTypeCanHaveProof boolean not null,

	primary key factTypePKey(factType)
) engine=innodb;
insert into FactType (factType, factTypeColour, factTypeCanHaveProof) values ('Axiom', '66DD66', false);
insert into FactType (factType, factTypeColour, factTypeCanHaveProof) values ('Definition', '6666DD', false);
insert into FactType (factType, factTypeColour, factTypeCanHaveProof) values ('Proposition', '66DDDD', true);
insert into FactType (factType, factTypeColour, factTypeCanHaveProof) values ('Theorem', 'DD6666', true);
insert into FactType (factType, factTypeColour, factTypeCanHaveProof) values ('Corollary', 'DDDD66', true);

create table Fact
(
	factID integer not null auto_increment,
	factName varchar(1000) not null,
	factType varchar(20) not null,
	factForCourse integer not null,
	factStatement varchar(8000) not null,
	factOrder integer not null,

	primary key factIDPKey(factID),
	foreign key factTypeFKey (factType) references FactType (factType),
	foreign key factForCourseFKey (factForCourse) references Course (courseID)
) engine=innodb;

create table Proof
(
	proofID integer not null auto_increment,
	proofName varchar(100) not null,
	proofText varchar(8000) not null,
	proofForFact integer not null,

	primary key proofIDPKey (proofID),
	foreign key proofForFactFKey (proofForFact) references Fact (factID)
) engine=innodb;

create table Dependency
(
 	dependencyID integer not null auto_increment,
	dependentTo integer not null,
	dependentOn integer not null,

	primary key dependencyIDPKey (dependencyID),
	foreign key dependentToFKey (dependentTo) references Proof (proofID),
	foreign key dependentOnFKey (dependentOn) references Fact (factID)
) engine=innodb;
