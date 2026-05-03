#ifndef WARD_H
#define WARD_H

#include "bed.h"

typedef struct Ward {
    int wardNumber;
    char wardName[MAX_NAME_LENGTH];
    int totalBeds;
    int occupiedBeds;
    Bed* bedList;
    struct Ward* next;
} Ward;

Ward* createWard(int wardNumber, const char* wardName, int totalBeds);
void addBedToWard(Ward* ward, Bed* bed);
Bed* findBedInWard(const Ward* ward, int bedNumber);
int getAvailableBedsInWard(const Ward* ward);
float getWardOccupancyRate(const Ward* ward);
void displayWard(const Ward* ward);
void displayWardBeds(const Ward* ward);
void freeWard(Ward* ward);

#endif