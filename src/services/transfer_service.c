#include "transfer_service.h"

int validateTransfer(Department* hospital, int patientId, int newDepartmentId, 
                     int newWardNumber, int newBedNumber, char* errorMessage) {
    PatientInfo info;
    
    if (!findPatientLocation(hospital, patientId, &info)) {
        sprintf(errorMessage, "找不到病人编号 %d", patientId);
        return FAILURE;
    }
    
    Department* dept = hospital;
    while (dept != NULL) {
        if (dept->departmentId == newDepartmentId) {
            Ward* ward = findWardInDepartment(dept, newWardNumber);
            if (ward == NULL) {
                sprintf(errorMessage, "找不到病房 %d", newWardNumber);
                return FAILURE;
            }
            
            Bed* bed = findBedInWard(ward, newBedNumber);
            if (bed == NULL) {
                sprintf(errorMessage, "找不到床位 %d", newBedNumber);
                return FAILURE;
            }
            
            if (!isBedAvailable(bed)) {
                sprintf(errorMessage, "床位 %d 已被占用", newBedNumber);
                return FAILURE;
            }
            
            return SUCCESS;
        }
        dept = dept->next;
    }
    
    sprintf(errorMessage, "找不到科室 %d", newDepartmentId);
    return FAILURE;
}

int transferPatient(Department* hospital, int patientId, int newDepartmentId, 
                    int newWardNumber, int newBedNumber) {
    char errorMessage[200];
    
    if (!validateTransfer(hospital, patientId, newDepartmentId, newWardNumber, newBedNumber, errorMessage)) {
        printf("错误：%s\n", errorMessage);
        return FAILURE;
    }
    
    PatientInfo oldInfo;
    findPatientLocation(hospital, patientId, &oldInfo);
    
    Department* oldDept = hospital;
    while (oldDept != NULL) {
        if (oldDept->departmentId == oldInfo.departmentId) {
            Ward* oldWard = findWardInDepartment(oldDept, oldInfo.wardNumber);
            Bed* oldBed = findBedInWard(oldWard, oldInfo.bedNumber);
            vacateBed(oldBed);
            oldWard->occupiedBeds--;
            updateDepartmentStats(oldDept);
            break;
        }
        oldDept = oldDept->next;
    }
    
    Department* newDept = hospital;
    while (newDept != NULL) {
        if (newDept->departmentId == newDepartmentId) {
            Ward* newWard = findWardInDepartment(newDept, newWardNumber);
            Bed* newBed = findBedInWard(newWard, newBedNumber);
            occupyBed(newBed, patientId, oldInfo.patientName);
            newWard->occupiedBeds++;
            updateDepartmentStats(newDept);
            break;
        }
        newDept = newDept->next;
    }
    
    printf("\n✓ 病人转科转床成功！\n");
    printf("  从: %s → 病房 %d → 床位 %d\n", 
           oldInfo.patientName, oldInfo.wardNumber, oldInfo.bedNumber);
    printf("  到: 科室 %d → 病房 %d → 床位 %d\n", 
           newDepartmentId, newWardNumber, newBedNumber);
    
    return SUCCESS;
}