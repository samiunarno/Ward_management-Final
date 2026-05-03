# 🏥 Hospital Ward Management System

A comprehensive hospital management system written in C that manages departments, wards, beds, and patients using linked lists. Designed for first-year university students to understand data structures and memory management.

---

## 📋 Table of Contents

1. [System Overview](#system-overview)
2. [Features](#features)
3. [Architecture](#architecture)
4. [File Structure](#file-structure)
5. [Requirements](#requirements)
6. [Installation & Compilation](#installation--compilation)
7. [How to Run](#how-to-run)
8. [Menu Guide](#menu-guide)
9. [Usage Examples](#usage-examples)
10. [Initial Data](#initial-data)
11. [Testing](#testing)
12. [Troubleshooting](#troubleshooting)
13. [Memory Management](#memory-management)
14. [FAQs](#faqs)

---

## System Overview

This Hospital Ward Management System is a console-based application that helps manage:

- **Departments** (Cardiology, Surgery, Pediatrics)
- **Wards** within each department
- **Beds** within each ward
- **Patients** admitted to beds

The system uses **three-level linked lists** to connect departments → wards → beds, demonstrating dynamic memory allocation and pointer manipulation.

---

## Features

### Core Features

| Feature | Description |
|---------|-------------|
| ✅ **Admit Patient** | Register a new patient to a specific bed in a ward |
| ✅ **Transfer Patient** | Move a patient to a different bed/ward/department |
| ✅ **Discharge Patient** | Remove a patient and free up the bed |
| ✅ **Release Bed** | Manually free a specific bed |
| ✅ **View Departments** | Display all departments with statistics |
| ✅ **View Wards** | Display all wards with occupancy details |
| ✅ **View All Patients** | List all currently admitted patients |
| ✅ **Statistics Report** | Generate console and file reports |
| ✅ **Memory Cleanup** | Automatic memory deallocation on exit |

### Technical Features

- Three-level linked list implementation
- Modular code structure (separate modules for core, services, reports, utils)
- Input validation for all user inputs
- Memory leak prevention with complete cleanup
- File export for statistical reports
- Professional error handling

---

## Architecture

### Data Structure Hierarchy
┌─────────────────────────────────────────────────────────────┐
│ DEPARTMENT (Level 1) │
│ • Department ID │
│ • Department Name │
│ • Pointer to next department │
│ • Pointer to first ward │
└─────────────────────────┬───────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│ WARD (Level 2) │
│ • Ward Number │
│ • Ward Name │
│ • Total Beds │
│ • Occupied Beds │
│ • Pointer to next ward │
│ • Pointer to first bed │
└─────────────────────────┬───────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│ BED (Level 3) │
│ • Bed Number │
│ • Status (Occupied/Available) │
│ • Patient ID │
│ • Patient Name │
│ • Pointer to next bed │
└─────────────────────────────────────────────────────────────┘

text

### Module Structure
┌─────────────────────────────────────────────────────────────┐
│ main.c │
│ (Program Entry Point) │
└─────────────────────────┬───────────────────────────────────┘
│
┌────────────────┼────────────────┐
│ │ │
▼ ▼ ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│ core/ │ │ services/ │ │ reports/ │
│ Department │ │ Patient │ │ Statistics │
│ Ward │ │ Transfer │ │ │
│ Bed │ │ │ │ │
└─────────────┘ └─────────────┘ └─────────────┘
│ │ │
└────────────────┼────────────────┘
│
▼
┌─────────────┐
│ utils/ │
│ Memory │
│ Validator │
└─────────────┘

text

---

## File Structure
hospital-management-system/
│
├── 📁 include/
│ └── common.h # Common definitions and constants
│
├── 📁 src/
│ ├── main.c # Main program with menu
│ │
│ ├── 📁 core/ # Core data structures
│ │ ├── bed.c # Bed operations
│ │ ├── bed.h # Bed declarations
│ │ ├── ward.c # Ward operations
│ │ ├── ward.h # Ward declarations
│ │ ├── department.c # Department operations
│ │ └── department.h # Department declarations
│ │
│ ├── 📁 services/ # Business logic
│ │ ├── patient_service.c # Patient admission/discharge
│ │ ├── patient_service.h # Patient service declarations
│ │ ├── transfer_service.c # Transfer logic
│ │ └── transfer_service.h # Transfer declarations
│ │
│ ├── 📁 reports/ # Reporting module
│ │ ├── statistics.c # Statistics generation
│ │ └── statistics.h # Statistics declarations
│ │
│ └── 📁 utils/ # Utility functions
│ ├── memory_manager.c # Memory cleanup
│ ├── memory_manager.h # Memory declarations
│ ├── validator.c # Input validation
│ └── validator.h # Validator declarations
│
├── 📄 Makefile # Build automation
├── 📄 README.md # This file
├── 📄 test_instructions.txt # Testing guide
└── 📄 memory_test.txt # Memory test records

text

---

## Requirements

### Software Requirements

| Requirement | Version | Notes |
|-------------|---------|-------|
| **GCC Compiler** | 4.8+ | For compiling C code |
| **Make** | 3.8+ | Optional, for using Makefile |
| **Valgrind** | 3.10+ | Optional, for memory leak testing (Linux only) |

### Supported Operating Systems

| OS | Compiler | Status |
|----|----------|--------|
| **Linux (Ubuntu/Debian)** | GCC | ✅ Fully Supported |
| **Linux (Fedora/RHEL)** | GCC | ✅ Fully Supported |
| **MacOS** | Clang/GCC | ✅ Fully Supported |
| **Windows** | MinGW | ✅ Fully Supported |
| **Windows** | WSL | ✅ Fully Supported |

---

## Installation & Compilation

### Step 1: Save All Files

Create the directory structure and save all the source code files as shown in the [File Structure](#file-structure) section.

### Step 2: Open Terminal

**Windows:**
```cmd
# Open Command Prompt or PowerShell
cd C:\path\to\hospital-management-system
Mac/Linux:

bash
# Open Terminal
cd /path/to/hospital-management-system
Step 3: Compile
Method A: Using Makefile (Recommended)
bash
make          # Compile the program
make clean    # Clean compiled files
make run      # Compile and run
make valgrind # Run with memory leak detection (Linux)
Method B: Manual Compilation
Linux/Mac:

bash
───────────────┐
│ WARD (Level 2) │
│ • Ward Number │
│ • Ward Name │
│ • Total Beds │
│ • Occupied Beds │
│ • Pointer to next ward │
│ • Pointer to first bed │
└─────────────────────────┬───────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│ BED (Level 3) │
│ • Bed Number │
│ • Status (Occupied/Available) │
│ • Patient ID │
│ • Patient Name │
│ • Pointer to next bed │
└─────────────────────────────────────────────────────────────┘

text

### Module Structure
┌─────────────────────────────────────────────────────────────┐
│ main.c │
│ (Program Entry Point) │
└─────────────────────────┬───────────────────────────────────┘
│
┌────────────────┼────────────────┐
│ │ │
▼ ▼ ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│ core/ │ │ services/ │ │ reports/ │
│ Department │ │ Patient │ │ Statistics │
│ Ward │ │ Transfer │ │ │
│ Bed │ │ │ │ │
└─────────────┘ └─────────────┘ └─────────────┘
│ │ │
└────────────────┼────────────────┘
│
▼
┌─────────────┐
│ utils/ │
│ Memory │
│ Validator │
└─────────────┘

text

---

## File Structure
hospital-management-system/
│
├── 📁 include/
│ └── common.h # Common definitions and constants
│
├── 📁 src/
│ ├── main.c # Main program with menu
│ │
│ ├── 📁 core/ # Core data structures
│ │ ├── bed.c # Bed operations
│ │ ├── bed.h # Bed declarations
│ │ ├── ward.c # Ward operations
│ │ ├── ward.h # Ward declarations
│ │ ├── department.c # Department operations
│ │ └── department.h # Department declarations
│ │
│ ├── 📁 services/ # Business logic
│ │ ├── patient_service.c # Patient admission/discharge
│ │ ├── patient_service.h # Patient service declarations
│ │ ├── transfer_service.c # Transfer logic
│ │ └── transfer_service.h # Transfer declarations
│ │
│ ├── 📁 reports/ # Reporting module
│ │ ├── statistics.c # Statistics generation
│ │ └── statistics.h # Statistics declarations
│ │
│ └── 📁 utils/ # Utility functions
│ ├── memory_manager.c # Memory cleanup
│ ├── memory_manager.h # Memory declarations
│ ├── validator.c # Input validation
│ └── validator.h # Validator declarations
│
├── 📄 Makefile # Build automation
├── 📄 README.md # This file
├── 📄 test_instructions.txt # Testing guide
└── 📄 memory_test.txt # Memory test records


---

## Requirements

### Software Requirements

| Requirement | Version | Notes |
|-------------|---------|-------|
| **GCC Compiler** | 4.8+ | For compiling C code |
| **Make** | 3.8+ | Optional, for using Makefile |
| **Valgrind** | 3.10+ | Optional, for memory leak testing (Linux only) |

### Supported Operating Systems

| OS | Compiler | Status |
|----|----------|--------|
| **Linux (Ubuntu/Debian)** | GCC | ✅ Fully Supported |
| **Linux (Fedora/RHEL)** | GCC | ✅ Fully Supported |
| **MacOS** | Clang/GCC | ✅ Fully Supported |
| **Windows** | MinGW | ✅ Fully Supported |
| **Windows** | WSL | ✅ Fully Supported |

---

## Installation & Compilation

### Step 1: Save All Files

Create the directory structure and save all the source code files as shown in the [File Structure](#file-structure) section.

### Step 2: Open Terminal

make          # Compile the program
make clean    # Clean compiled files
make run      # Compile and run
make valgrind # Run with memory leak detection (Linux)