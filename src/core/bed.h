#ifndef BED_H
#define BED_H
#include "../../include/common.h"

typedef struct Bed {

    int bedNumber;
    BedStatus status;
    int patientId;
    char patientName[100];
    struct Bed* next;

} Bed ;


Bed* createBed(int bedNumber);
void initalizeBed(Bed* bed , int bedNumber);
void occupyBed(Bed* bed , int patientId,const char* patientName);
void vacateBed(Bed* bed);

int isBedAvailable(const Bed*bed);
void displayBed(const Bed* bed);
void freeBed(Bed* bed);
#endif