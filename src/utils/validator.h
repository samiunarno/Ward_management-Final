#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "../../include/common.h"

int isValidPatientId(int patientId);
int isValidBedNumber(int bedNumber, int maxBeds);
int isValidWardNumber(int wardNumber);
int isValidDepartmentId(int departmentId);
int isValidName(const char* name);
int getValidatedIntInput(const char* prompt, int min, int max);
void getValidatedStringInput(const char* prompt, char* buffer, int maxLength);

#endif