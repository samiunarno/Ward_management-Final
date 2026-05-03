#include "patient_service.h"

int admitPatient(Department* hospital, int departmentId, int wardNumber, 
                 int bedNumber, int patientId, const char* patientName) {
    if (hospital == NULL) return FAILURE;
    
    Department* dept = hospital;
    while (dept != NULL) {
        if (dept->departmentId == departmentId) {
            Ward* ward = findWardInDepartment(dept, wardNumber);
            if (ward == NULL) {
                printf("错误：科室 %d 中找不到病房 %d\n", departmentId, wardNumber);
                return FAILURE;
            }
            
            Bed* bed = findBedInWard(ward, bedNumber);
            if (bed == NULL) {
                printf("错误：病房 %d 中找不到床位 %d\n", wardNumber, bedNumber);
                return FAILURE;
            }
            
            if (!isBedAvailable(bed)) {
                printf("错误：床位 %d 已被占用\n", bedNumber);
                return FAILURE;
            }
            
            occupyBed(bed, patientId, patientName);
            ward->occupiedBeds++;
            updateDepartmentStats(dept);
            
            printf("\n✓ 病人入院登记成功！\n");
            printf("  科室: %s\n", dept->departmentName);
            printf("  病房: %d - %s\n", ward->wardNumber, ward->wardName);
            printf("  床位: %d\n", bed->bedNumber);
            printf("  病人: %s (编号: %d)\n", patientName, patientId);
            
            return SUCCESS;
        }
        dept = dept->next;
    }
    
    printf("错误：找不到科室 %d\n", departmentId);
    return FAILURE;
}

int dischargePatient(Department* hospital, int patientId) {
    if (hospital == NULL) return FAILURE;
    
    Department* dept = hospital;
    while (dept != NULL) {
        Ward* ward = dept->wardList;
        while (ward != NULL) {
            Bed* bed = ward->bedList;
            while (bed != NULL) {
                if (bed->status == STATUS_OCCUPIED && bed->patientId == patientId) {
                    printf("\n找到病人信息：\n");
                    printf("  姓名: %s\n", bed->patientName);
                    printf("  科室: %s\n", dept->departmentName);
                    printf("  病房: %d\n", ward->wardNumber);
                    printf("  床位: %d\n", bed->bedNumber);
                    
                    char confirm;
                    printf("\n确认办理出院吗？(y/n): ");
                    scanf(" %c", &confirm);
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        vacateBed(bed);
                        ward->occupiedBeds--;
                        updateDepartmentStats(dept);
                        printf("\n✓ 病人出院办理成功！\n");
                        return SUCCESS;
                    } else {
                        printf("出院已取消\n");
                        return FAILURE;
                    }
                }
                bed = bed->next;
            }
            ward = ward->next;
        }
        dept = dept->next;
    }
    
    printf("错误：找不到病人编号 %d\n", patientId);
    return FAILURE;
}

int findPatientLocation(Department* hospital, int patientId, PatientInfo* info) {
    if (hospital == NULL || info == NULL) return FAILURE;
    
    Department* dept = hospital;
    while (dept != NULL) {
        Ward* ward = dept->wardList;
        while (ward != NULL) {
            Bed* bed = ward->bedList;
            while (bed != NULL) {
                if (bed->status == STATUS_OCCUPIED && bed->patientId == patientId) {
                    info->patientId = patientId;
                    strcpy(info->patientName, bed->patientName);
                    info->departmentId = dept->departmentId;
                    info->wardNumber = ward->wardNumber;
                    info->bedNumber = bed->bedNumber;
                    return SUCCESS;
                }
                bed = bed->next;
            }
            ward = ward->next;
        }
        dept = dept->next;
    }
    
    return FAILURE;
}

void displayAllPatients(Department* hospital) {
    if (hospital == NULL) return;
    
    printf("\n============================================================\n");
    printf("                    当前住院病人列表\n");
    printf("============================================================\n");
    
    int count = 0;
    Department* dept = hospital;
    
    while (dept != NULL) {
        Ward* ward = dept->wardList;
        while (ward != NULL) {
            Bed* bed = ward->bedList;
            while (bed != NULL) {
                if (bed->status == STATUS_OCCUPIED) {
                    count++;
                    printf("%2d. %-10s (编号:%-6d) %s → 病房 %d, 床位 %d\n",
                           count, bed->patientName, bed->patientId,
                           dept->departmentName, ward->wardNumber, bed->bedNumber);
                }
                bed = bed->next;
            }
            ward = ward->next;
        }
        dept = dept->next;
    }
    
    if (count == 0) {
        printf("                    当前没有住院病人\n");
    }
    
    printf("============================================================\n");
}