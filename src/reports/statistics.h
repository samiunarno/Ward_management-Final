#ifndef STATISTICS_H
#define STATISTICS_H

#include "../core/department.h"
#include "../../include/common.h"

typedef struct HospitalStatistics {
    int totalDepartments;
    int totalWards;
    int totalBeds;
    int totalPatients;
    float overallOccupancyRate;
    float departmentOccupancyRates[MAX_DEPARTMENTS];
    char departmentNames[MAX_DEPARTMENTS][MAX_NAME_LENGTH];
    int departmentCount;
} HospitalStatistics;

void generateStatisticsReport(Department* hospital, ReportType type);
HospitalStatistics collectStatistics(Department* hospital);
void displayStatisticsReport(const HospitalStatistics* stats);
void exportStatisticsToFile(const HospitalStatistics* stats, const char* filename);
void printDepartmentDetails(Department* hospital);
void printWardDetails(Department* hospital);

#endif