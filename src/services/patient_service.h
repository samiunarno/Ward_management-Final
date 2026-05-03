#ifndef PATIENT_SERVICE_H
#define PATIENT_SERVICE_H

#include "../core/department.h"

typedef struct PatientInfo {
    int patientId;
    char patientName[MAX_NAME_LENGTH];
    int departmentId;
    int wardNumber;
    int bedNumber;
} PatientInfo;

int admitPatient(Department* hospital, int departmentId, int wardNumber, 
                 int bedNumber, int patientId, const char* patientName);
int dischargePatient(Department* hospital, int patientId);
int findPatientLocation(Department* hospital, int patientId, PatientInfo* info);
void displayAllPatients(Department* hospital);

#endif