#pragma once

#include <iostream>

typedef std::string FactType;

typedef struct Fact
{
    int id;
    int parent;
    std::string name;
    FactType type;
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