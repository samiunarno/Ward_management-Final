#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "ward.h"

typedef struct Department {
    int departmentId;
    char departmentName[MAX_NAME_LENGTH];
    int totalWards;
    int totalBeds;
    int totalPatients;
    Ward* wardList;
    struct Department* next;
} Department;

Department* createDepartment(int departmentId, const char* departmentName);
void addWardToDepartment(Department* department, Ward* ward);
Ward* findWardInDepartment(const Department* department, int wardNumber);
void updateDepartmentStats(Department* department);
void displayDepartment(const Department* department);
void displayDepartmentWards(const Department* department);
void freeDepartment(Department* department);

#endif