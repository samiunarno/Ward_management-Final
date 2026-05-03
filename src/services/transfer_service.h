#ifndef TRANSFER_SERVICE_H
#define TRANSFER_SERVICE_H

#include "../core/department.h"
#include "patient_service.h"

int transferPatient(Department* hospital, int patientId, int newDepartmentId, 
                    int newWardNumber, int newBedNumber);
int validateTransfer(Department* hospital, int patientId, int newDepartmentId, 
                     int newWardNumber, int newBedNumber, char* errorMessage);

#endif