#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "../core/department.h"

typedef struct {
    int bedsFreed;
    int wardsFreed;
    int departmentsFreed;
    int totalAllocations;
    int totalDeallocations;
} MemoryStats;

void freeHospitalSystem(Department** hospital);
MemoryStats getMemoryStats(void);
void resetMemoryStats(void);
void trackAllocation(void);
void trackDeallocation(void);
void printMemoryReport(void);

#endif