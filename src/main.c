#include "core/department.h"
#include "services/patient_service.h"
#include "services/transfer_service.h"
#include "reports/statistics.h"
#include "utils/memory_manager.h"
#include "utils/validator.h"

void printMainMenu(void) {
    printf("\n");
    printf("============================================================\n");
    printf("                    医院管理系统\n");
    printf("============================================================\n");
    printf("  1.  入院登记\n");
    printf("  2.  转床/转科\n");
    printf("  3.  出院办理\n");
    printf("  4.  释放床位\n");
    printf("  5.  查看科室信息\n");
    printf("  6.  查看病房信息\n");
    printf("  7.  查看所有病人\n");
    printf("  8.  生成统计报告\n");
    printf("  9.  退出系统\n");
    printf("============================================================\n");
}

Department* initializeHospital(void) {
    printf("\n============================================================\n");
    printf("                    正在初始化医院系统\n");
    printf("============================================================\n");
    
    Department* hospital = createDepartment(1, "心血管内科");
    Ward* ward101 = createWard(101, "心血管普通病房", 3);
    Ward* ward102 = createWard(102, "心血管重症监护室", 2);
    addWardToDepartment(hospital, ward101);
    addWardToDepartment(hospital, ward102);
    
    Department* dept2 = createDepartment(2, "外科");
    Ward* ward201 = createWard(201, "外科普通病房", 3);
    addWardToDepartment(dept2, ward201);
    
    Department* dept3 = createDepartment(3, "儿科");
    Ward* ward301 = createWard(301, "儿科病房", 2);
    addWardToDepartment(dept3, ward301);
    
    hospital->next = dept2;
    dept2->next = dept3;
    
    printf("\n✓ 医院系统初始化成功！\n");
    printf("  - 3 个科室\n");
    printf("  - 4 个病房\n");
    printf("  - 10 张床位\n\n");
    
    return hospital;
}

void handleAdmitPatient(Department* hospital) {
    printf("\n========== 入院登记 ==========\n");
    
    int deptId = getValidatedIntInput("请输入科室编号 (1-3): ", 1, 3);
    int wardNum = getValidatedIntInput("请输入病房号 (101/102/201/301): ", 101, 301);
    int bedNum = getValidatedIntInput("请输入床位号 (1-3): ", 1, 3);
    int patientId = getValidatedIntInput("请输入病人编号: ", 1, 99999);
    
    char patientName[MAX_NAME_LENGTH];
    printf("请输入病人姓名: ");
    scanf("%s", patientName);
    
    admitPatient(hospital, deptId, wardNum, bedNum, patientId, patientName);
}

void handleTransferPatient(Department* hospital) {
    printf("\n========== 转床/转科 ==========\n");
    
    int patientId = getValidatedIntInput("请输入要转科的病人编号: ", 1, 99999);
    int newDeptId = getValidatedIntInput("请输入新科室编号 (1-3): ", 1, 3);
    int newWardNum = getValidatedIntInput("请输入新病房号: ", 101, 301);
    int newBedNum = getValidatedIntInput("请输入新床位号: ", 1, 3);
    
    transferPatient(hospital, patientId, newDeptId, newWardNum, newBedNum);
}

void handleDischargePatient(Department* hospital) {
    printf("\n========== 出院办理 ==========\n");
    int patientId = getValidatedIntInput("请输入要出院的病人编号: ", 1, 99999);
    dischargePatient(hospital, patientId);
}

void handleReleaseBed(Department* hospital) {
    printf("\n========== 释放床位 ==========\n");
    int deptId = getValidatedIntInput("请输入科室编号: ", 1, 3);
    int wardNum = getValidatedIntInput("请输入病房号: ", 101, 301);
    int bedNum = getValidatedIntInput("请输入床位号: ", 1, 3);
    
    Department* dept = hospital;
    while (dept != NULL) {
        if (dept->departmentId == deptId) {
            Ward* ward = findWardInDepartment(dept, wardNum);
            if (ward != NULL) {
                Bed* bed = findBedInWard(ward, bedNum);
                if (bed != NULL && bed->status == STATUS_OCCUPIED) {
                    printf("\n床位 %d 当前病人: %s (编号: %d)\n", 
                           bedNum, bed->patientName, bed->patientId);
                    char confirm;
                    printf("确认释放该床位吗？(y/n): ");
                    scanf(" %c", &confirm);
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        vacateBed(bed);
                        ward->occupiedBeds--;
                        updateDepartmentStats(dept);
                        printf("✓ 床位释放成功！\n");
                    }
                } else if (bed != NULL) {
                    printf("床位 %d 已经是空闲状态。\n", bedNum);
                }
            }
            break;
        }
        dept = dept->next;
    }
}

int main(void) {
    Department* hospital = initializeHospital();
    int choice;
    
    do {
        printMainMenu();
        choice = getValidatedIntInput("请选择功能 (1-9): ", 1, 9);
        
        switch(choice) {
            case 1:
                handleAdmitPatient(hospital);
                break;
            case 2:
                handleTransferPatient(hospital);
                break;
            case 3:
                handleDischargePatient(hospital);
                break;
            case 4:
                handleReleaseBed(hospital);
                break;
            case 5:
                printDepartmentDetails(hospital);
                break;
            case 6:
                printWardDetails(hospital);
                break;
            case 7:
                displayAllPatients(hospital);
                break;
            case 8:
                generateStatisticsReport(hospital, REPORT_BOTH);
                break;
            case 9:
                printf("\n正在退出系统...\n");
                freeHospitalSystem(&hospital);
                printMemoryReport();
                printf("\n感谢使用医院管理系统！\n");
                break;
        }
    } while(choice != 9);
    
    return 0;
}