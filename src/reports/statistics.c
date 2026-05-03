#include "statistics.h"

HospitalStatistics collectStatistics(Department* hospital) {
    HospitalStatistics stats;
    memset(&stats, 0, sizeof(stats));
    
    Department* dept = hospital;
    int deptIndex = 0;
    
    while (dept != NULL && deptIndex < MAX_DEPARTMENTS) {
        stats.totalDepartments++;
        stats.totalWards += dept->totalWards;
        stats.totalBeds += dept->totalBeds;
        stats.totalPatients += dept->totalPatients;
        
        if (dept->totalBeds > 0) {
            stats.departmentOccupancyRates[deptIndex] = 
                (float)dept->totalPatients / dept->totalBeds * 100;
        }
        strcpy(stats.departmentNames[deptIndex], dept->departmentName);
        deptIndex++;
        
        dept = dept->next;
    }
    
    stats.departmentCount = deptIndex;
    
    if (stats.totalBeds > 0) {
        stats.overallOccupancyRate = (float)stats.totalPatients / stats.totalBeds * 100;
    }
    
    return stats;
}

void displayStatisticsReport(const HospitalStatistics* stats) {
    printf("\n");
    printf("============================================================\n");
    printf("                    医院统计报告\n");
    printf("============================================================\n");
    
    time_t t;
    time(&t);
    printf("报告日期: %s", ctime(&t));
    printf("============================================================\n");
    
    printf("医院总体情况\n");
    printf("  总科室数:       %d\n", stats->totalDepartments);
    printf("  总病房数:       %d\n", stats->totalWards);
    printf("  总床位数:       %d\n", stats->totalBeds);
    printf("  总病人数:       %d\n", stats->totalPatients);
    printf("  全院入住率:     %.1f%%\n", stats->overallOccupancyRate);
    
    printf("============================================================\n");
    printf("各科室详情\n");
    
    for (int i = 0; i < stats->departmentCount; i++) {
        printf("  %-15s %.1f%% 入住率\n", 
               stats->departmentNames[i], stats->departmentOccupancyRates[i]);
    }
    
    printf("============================================================\n");
}

void exportStatisticsToFile(const HospitalStatistics* stats, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("错误：无法创建报告文件\n");
        return;
    }
    
    fprintf(file, "============================================================\n");
    fprintf(file, "医院统计报告\n");
    fprintf(file, "============================================================\n\n");
    
    time_t t;
    time(&t);
    fprintf(file, "报告日期: %s\n\n", ctime(&t));
    
    fprintf(file, "医院总体情况\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "总科室数:       %d\n", stats->totalDepartments);
    fprintf(file, "总病房数:       %d\n", stats->totalWards);
    fprintf(file, "总床位数:       %d\n", stats->totalBeds);
    fprintf(file, "总病人数:       %d\n", stats->totalPatients);
    fprintf(file, "全院入住率:     %.1f%%\n\n", stats->overallOccupancyRate);
    
    fprintf(file, "各科室详情\n");
    fprintf(file, "------------------------------------------------------------\n");
    for (int i = 0; i < stats->departmentCount; i++) {
        fprintf(file, "%s: %.1f%% 入住率\n", 
                stats->departmentNames[i], stats->departmentOccupancyRates[i]);
    }
    
    fclose(file);
    printf("\n✓ 报告已导出到 '%s'\n", filename);
}

void generateStatisticsReport(Department* hospital, ReportType type) {
    HospitalStatistics stats = collectStatistics(hospital);
    
    if (type == REPORT_CONSOLE || type == REPORT_BOTH) {
        displayStatisticsReport(&stats);
    }
    
    if (type == REPORT_FILE || type == REPORT_BOTH) {
        exportStatisticsToFile(&stats, "hospital_report.txt");
    }
}

void printDepartmentDetails(Department* hospital) {
    if (hospital == NULL) return;
    
    printf("\n============================================================\n");
    printf("                    科室详细信息\n");
    printf("============================================================\n");
    
    Department* dept = hospital;
    while (dept != NULL) {
        displayDepartment(dept);
        dept = dept->next;
    }
}

void printWardDetails(Department* hospital) {
    if (hospital == NULL) return;
    
    printf("\n============================================================\n");
    printf("                    病房详细信息\n");
    printf("============================================================\n");
    
    Department* dept = hospital;
    while (dept != NULL) {
        Ward* ward = dept->wardList;
        while (ward != NULL) {
            printf("\n所属科室: %s\n", dept->departmentName);
            displayWard(ward);
            ward = ward->next;
        }
        dept = dept->next;
    }
}