CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -Iinclude
TARGET = hospital

SRCDIR = src
OBJDIR = obj

CORE_SRCS = $(SRCDIR)/core/bed.c $(SRCDIR)/core/ward.c $(SRCDIR)/core/department.c
SERVICE_SRCS = $(SRCDIR)/services/patient_service.c $(SRCDIR)/services/transfer_service.c
REPORT_SRCS = $(SRCDIR)/reports/statistics.c
UTIL_SRCS = $(SRCDIR)/utils/memory_manager.c $(SRCDIR)/utils/validator.c
MAIN_SRC = $(SRCDIR)/main.c

ALL_SRCS = $(MAIN_SRC) $(CORE_SRCS) $(SERVICE_SRCS) $(REPORT_SRCS) $(UTIL_SRCS)

all: clean $(TARGET)

$(TARGET): $(ALL_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) hospital_report.txt

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

.PHONY: all clean run valgrind debug