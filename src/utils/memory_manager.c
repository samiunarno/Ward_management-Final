#include "memory_manager.h"

static MemoryStats stats = {0, 0, 0, 0, 0};

void freeHospitalSystem(Department** hospital) {
    if (hospital == NULL || *hospital == NULL) return;
    
    printf("\n============================================================\n");
    printf("                    内存清理中\n");
    printf("============================================================\n");
    
    Department* current = *hospital;
    stats.departmentsFreed = 0;
    stats.wardsFreed = 0;
    stats.bedsFreed = 0;
    
    while (current != NULL) {
        Department* nextDept = current->next;
        
        Ward* currentWard = current->wardList;
        while (currentWard != NULL) {
            Ward* nextWard = currentWard->next;
            
            Bed* currentBed = currentWard->bedList;
            while (currentBed != NULL) {
                Bed* nextBed = currentBed->next;
                free(currentBed);
                stats.bedsFreed++;
                trackDeallocation();
                currentBed = nextBed;
            }
            
            free(currentWard);
            stats.wardsFreed++;
            currentWard = nextWard;
        }
        
        free(current);
        stats.departmentsFreed++;
        current = nextDept;
    }
    
    *hospital = NULL;
    
    printf("\n✓ 内存清理完成：\n");
    printf("  - 释放了 %d 张床位\n", stats.bedsFreed);
    printf("  - 释放了 %d 个病房\n", stats.wardsFreed);
    printf("  - 释放了 %d 个科室\n", stats.departmentsFreed);
}

MemoryStats getMemoryStats(void) {
    return stats;
}

void resetMemoryStats(void) {
    memset(&stats, 0, sizeof(stats));
}

void trackAllocation(void) {
    stats.totalAllocations++;
}

void trackDeallocation(void) {
    stats.totalDeallocations++;
}

void printMemoryReport(void) {
    printf("\n============================================================\n");
    printf("                    内存使用报告\n");
    printf("============================================================\n");
    printf("总分配次数:     %d\n", stats.totalAllocations);
    printf("总释放次数:     %d\n", stats.totalDeallocations);
    printf("当前使用中:     %d\n", stats.totalAllocations - stats.totalDeallocations);
    
    if (stats.totalAllocations == stats.totalDeallocations) {
        printf("状态: ✓ 未检测到内存泄漏\n");
    } else {
        printf("状态: ⚠ 可能存在内存泄漏\n");
    }
    printf("============================================================\n");
}