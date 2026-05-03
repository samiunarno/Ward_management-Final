#include "ward.h"

Ward* createWard(int wardNumber, const char* wardName, int totalBeds) {
    Ward* ward = (Ward*)malloc(sizeof(Ward));
    if (ward == NULL) {
        printf("病房内存分配失败\n");
        return NULL;
    }
    
    ward->wardNumber = wardNumber;
    strcpy(ward->wardName, wardName);
    ward->totalBeds = totalBeds;
    ward->occupiedBeds = 0;
    ward->bedList = NULL;
    ward->next = NULL;
    
    for (int i = 1; i <= totalBeds; i++) {
        Bed* bed = createBed(i);
        addBedToWard(ward, bed);
    }
    
    return ward;
}

void addBedToWard(Ward* ward, Bed* bed) {
    if (ward == NULL || bed == NULL) return;
    
    if (ward->bedList == NULL) {
        ward->bedList = bed;
    } else {
        Bed* current = ward->bedList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = bed;
    }
}

Bed* findBedInWard(const Ward* ward, int bedNumber) {
    if (ward == NULL) return NULL;
    
    Bed* current = ward->bedList;
    while (current != NULL) {
        if (current->bedNumber == bedNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int getAvailableBedsInWard(const Ward* ward) {
    if (ward == NULL) return 0;
    return ward->totalBeds - ward->occupiedBeds;
}

float getWardOccupancyRate(const Ward* ward) {
    if (ward == NULL || ward->totalBeds == 0) return 0.0f;
    return (float)ward->occupiedBeds / ward->totalBeds * 100;
}

void displayWard(const Ward* ward) {
    if (ward == NULL) return;
    
    printf("\n============================================================\n");
    printf("病房 %d: %s\n", ward->wardNumber, ward->wardName);
    printf("入住率: %d/%d 床位 (%.1f%%)\n", 
           ward->occupiedBeds, ward->totalBeds, getWardOccupancyRate(ward));
    printf("------------------------------------------------------------\n");
    displayWardBeds(ward);
    printf("============================================================\n");
}

void displayWardBeds(const Ward* ward) {
    if (ward == NULL) return;
    
    Bed* current = ward->bedList;
    while (current != NULL) {
        displayBed(current);
        current = current->next;
    }
}

void freeWard(Ward* ward) {
    if (ward == NULL) return;
    
    Bed* current = ward->bedList;
    while (current != NULL) {
        Bed* next = current->next;
        freeBed(current);
        current = next;
    }
    
    free(ward);
}