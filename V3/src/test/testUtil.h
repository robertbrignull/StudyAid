#pragma once

class TestUtil
{
public:
    static void addCourse(StudyAid *window, const char *name);
    static void editCurrentCourse(StudyAid *window, const char *name);
    static void deleteCurrentCourse(StudyAid *window);

    static void addFact(StudyAid *window, const char *name, const char *type);
    static void editCurrentFact(StudyAid *window, const char *name, const char *type);
    static void editCurrentFactStatement(StudyAid *window, const char *statement);
    static void deleteCurrentFact(StudyAid *window);
};