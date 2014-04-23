#pragma once

#include <iostream>

#include <QMetaType>

typedef struct FactType
{
    std::string fact_type;
    bool can_have_proof;
    std::string colour;
} FactType;

typedef struct Fact
{
    int id;
    int parent;
    std::string name;
    std::string type;
    std::string statement;
    int ordering;
} Fact;

typedef struct Proof
{
    int id;
    int fact;
    std::string name;
    std::string body;
    int ordering;
} Proof;

typedef struct Course
{
    int id;
    std::string name;
    int ordering;
    int root_fact;
} Course;



class NotFoundException : public std::exception { };



Q_DECLARE_METATYPE(FactType);
Q_DECLARE_METATYPE(Fact);
Q_DECLARE_METATYPE(Proof);
Q_DECLARE_METATYPE(Course);