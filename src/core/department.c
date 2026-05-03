#include "department.h"

Department* createDepartment(int departmentId, const char* departmentName) {
    Department* department = (Department*)malloc(sizeof(Department));
    if (department == NULL) {
        printf("科室内存分配失败\n");
        return NULL;
    }
    
    department->departmentId = departmentId;
    strcpy(department->departmentName, departmentName);
    department->totalWards = 0;
    department->totalBeds = 0;
    department->totalPatients = 0;
    department->wardList = NULL;
    department->next = NULL;
    
    return department;
}

void addWardToDepartment(Department* department, Ward* ward) {
    if (department == NULL || ward == NULL) return;
    
    if (department->wardList == NULL) {
        department->wardList = ward;
    } else {
        Ward* current = department->wardList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = ward;
    }
    
    department->totalWards++;
    department->totalBeds += ward->totalBeds;
    updateDepartmentStats(department);
}

Ward* findWardInDepartment(const Department* department, int wardNumber) {
    if (department == NULL) return NULL;
    
    Ward* current = department->wardList;
    while (current != NULL) {
        if (current->wardNumber == wardNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateDepartmentStats(Department* department) {
    if (department == NULL) return;
    
    department->totalPatients = 0;
    Ward* current = department->wardList;
    
    while (current != NULL) {
        department->totalPatients += current->occupiedBeds;
        current = current->next;
    }
}

void displayDepartment(const Department* department) {
    if (department == NULL) return;
    
    printf("\n============================================================\n");
    printf("科室: %s (编号: %d)\n", department->departmentName, department->departmentId);
    printf("统计: %d 位病人 | %d 张床位 | %d 个病房\n", 
           department->totalPatients, department->totalBeds, department->totalWards);
    printf("============================================================\n");
    displayDepartmentWards(department);
}

void displayDepartmentWards(const Department* department) {
    if (department == NULL) return;
    
    Ward* current = department->wardList;
    while (current != NULL) {
        displayWard(current);
        current = current->next;
    }
}

void freeDepartment(Department* department) {
    if (department == NULL) return;
    
    Ward* current = department->wardList;
    while (current != NULL) {
        Ward* next = current->next;
        freeWard(current);
        current = next;
    }
    
    free(department);
}