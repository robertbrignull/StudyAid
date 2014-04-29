#pragma once

class FactList;
class SectionPickerWidget;

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

    static void addProof(StudyAid *window, const char *name);
    static void editCurrentProof(StudyAid *window, const char *name);
    static void editCurrentProofBody(StudyAid *window, const char *body);
    static void deleteCurrentProof(StudyAid *window);

    static void addFactToSection(StudyAid *window, const char *factName, const char *factType, const char *sectionName);
    static void editSection(StudyAid *window, const char *newSectionName, const char *oldSectionName);
    static void deleteSection(StudyAid *window, const char *sectionName);
    static void selectSection(StudyAid *window, const char *sectionName);
    static FactList *findFactList(StudyAid *window, const char *name, FactList *searchRoot);
    static SectionPickerWidget *findSectionPicker(StudyAid *window, const char *name, SectionPickerWidget *searchRoot);
};