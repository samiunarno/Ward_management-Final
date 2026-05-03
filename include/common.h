#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 100
#define MAX_DEPARTMENTS 10
#define MAX_WARDS_PER_DEPT 10
#define MAX_BEDS_PER_WARD 20
#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0

typedef enum {
    STATUS_AVAILABLE = 0,
    STATUS_OCCUPIED = 1
} BedStatus;

typedef enum {
    REPORT_CONSOLE = 1,
    REPORT_FILE = 2,
    REPORT_BOTH = 3
} ReportType;

#endif