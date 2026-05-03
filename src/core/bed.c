#include "bed.h"

Bed* createBed(int bedNumber) {
    Bed* bed = (Bed*)malloc(sizeof(Bed));
    if (bed == NULL) {
        printf("床位内存分配失败\n");
        return NULL;
    }
    initializeBed(bed, bedNumber);
    return bed;
}

void initializeBed(Bed* bed, int bedNumber) {
    bed->bedNumber = bedNumber;
    bed->status = STATUS_AVAILABLE;
    bed->patientId = -1;
    strcpy(bed->patientName, "");
    bed->next = NULL;
}

void occupyBed(Bed* bed, int patientId, const char* patientName) {
    if (bed == NULL) return;
    bed->status = STATUS_OCCUPIED;
    bed->patientId = patientId;
    strcpy(bed->patientName, patientName);
}

void vacateBed(Bed* bed) {
    if (bed == NULL) return;
    bed->status = STATUS_AVAILABLE;
    bed->patientId = -1;
    strcpy(bed->patientName, "");
}

int isBedAvailable(const Bed* bed) {
    return bed != NULL && bed->status == STATUS_AVAILABLE;
}

void displayBed(const Bed* bed) {
    if (bed == NULL) return;
    
    if (bed->status == STATUS_OCCUPIED) {
        printf("  床位 %2d: [已占用] 病人: %s (编号: %d)\n", 
               bed->bedNumber, bed->patientName, bed->patientId);
    } else {
        printf("  床位 %2d: [空闲]\n", bed->bedNumber);
    }
}

void freeBed(Bed* bed) {
    if (bed != NULL) {
        free(bed);
    }
}