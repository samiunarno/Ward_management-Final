#include "validator.h"

int isValidPatientId(int patientId) {
    return patientId > 0 && patientId < 100000;
}

int isValidBedNumber(int bedNumber, int maxBeds) {
    return bedNumber >= 1 && bedNumber <= maxBeds;
}

int isValidWardNumber(int wardNumber) {
    return wardNumber >= 100 && wardNumber <= 999;
}

int isValidDepartmentId(int departmentId) {
    return departmentId >= 1 && departmentId <= 99;
}

int isValidName(const char* name) {
    if (name == NULL) return FALSE;
    int len = strlen(name);
    return len > 0 && len < MAX_NAME_LENGTH;
}

int getValidatedIntInput(const char* prompt, int min, int max) {
    int value;
    int valid;
    
    do {
        printf("%s", prompt);
        valid = scanf("%d", &value);
        
        if (valid != 1) {
            printf("错误：请输入有效的数字\n");
            while (getchar() != '\n');
            valid = FALSE;
        } else if (value < min || value > max) {
            printf("错误：请输入 %d 到 %d 之间的数字\n", min, max);
            valid = FALSE;
        } else {
            valid = TRUE;
        }
        
    } while (!valid);
    
    return value;
}

void getValidatedStringInput(const char* prompt, char* buffer, int maxLength) {
    do {
        printf("%s", prompt);
        fgets(buffer, maxLength, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (strlen(buffer) == 0) {
            printf("错误：姓名不能为空\n");
        }
    } while (strlen(buffer) == 0);
}