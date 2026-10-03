#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "employees.h"

static int    empId[MAX_EMPLOYEES];
static char   empName[MAX_EMPLOYEES][NAME_LEN];
static char   empDept[MAX_EMPLOYEES][DEPT_LEN];
static double empBasic[MAX_EMPLOYEES];
static double empHousing[MAX_EMPLOYEES];
static double empTransport[MAX_EMPLOYEES];
static int    empCount = 0;

static int isBlank(const char *s)
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isspace((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}


static void readLine(const char *prompt, char *buf, int size)
{
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, size, stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            exit(0);
        }
        char *nl = strchr(buf, '\n');
        if (nl != NULL) {
            *nl = '\0';
        } else {
            int c;                       
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        if (isBlank(buf)) {
            printf("Input cannot be empty.\n");
        } else {
            return;
        }
    }
}


static int readInt(const char *prompt)
{
    char line[32];
    char *end;
    while (1) {
        readLine(prompt, line, sizeof line);
        long v = strtol(line, &end, 10);
        if (*end != '\0') {
            printf("Please enter a whole number.\n");
        } else {
            return (int)v;
        }
    }
}

static double readAmount(const char *prompt, int allowZero)
{
    char line[64];
    char *end;
    while (1) {
        readLine(prompt, line, sizeof line);
        double v = strtod(line, &end);
        if (*end != '\0') {
            printf("Invalid number. Enter digits only (e.g. 8500.50).\n");
        } else if (v < 0) {
            printf("Amount cannot be negative.\n");
        } else if (v == 0 && !allowZero) {
            printf("Amount must be greater than zero.\n");
        } else {
            return v;
        }
    }
}

static int findEmployeeById(int id)
{
    for (int i = 0; i < empCount; i++) {
        if (empId[i] == id) {
            return i;
        }
    }
    return -1;
}


static int sameName(const char *a, const char *b)
{
    char la[NAME_LEN], lb[NAME_LEN];
    int i;
    for (i = 0; a[i] != '\0' && i < NAME_LEN - 1; i++) {
        la[i] = (char)tolower((unsigned char)a[i]);
    }
    la[i] = '\0';
    for (i = 0; b[i] != '\0' && i < NAME_LEN - 1; i++) {
        lb[i] = (char)tolower((unsigned char)b[i]);
    }
    lb[i] = '\0';
    return strcmp(la, lb) == 0;
}

static void printEmployeeRow(int i)
{
    double gross = calculateGrossSalary(empBasic[i], empHousing[i], empTransport[i]);
    printf("%-6d %-22s %-14s N$%-10.2f N$%-10.2f N$%-10.2f N$%-10.2f\n",
           empId[i], empName[i], empDept[i],
           empBasic[i], empHousing[i], empTransport[i], gross);
}

static void printTableHeader(void)
{
    printf("\n%-6s %-22s %-14s %-12s %-12s %-12s %-12s\n",
           "ID", "Name", "Department", "Basic", "Housing", "Transport", "Gross");
    printf("--------------------------------------------------------------------------------------------\n");
}


double calculateGrossSalary(double basic, double housing, double transport)
{
    return basic + housing + transport;
}

double calculateDeduction(double gross)
{
    return gross * DEDUCTION_RATE;
}

double calculateNetSalary(double gross, double deduction)
{
    return gross - deduction;
}


void addEmployee(void)
{
    if (empCount >= MAX_EMPLOYEES) {
        printf("Employee list is full (%d).\n", MAX_EMPLOYEES);
        return;
    }

    int id;
    while (1) {
        id = readInt("Employee ID: ");
        if (id <= 0) {
            printf("ID must be a positive number.\n");
        } else if (findEmployeeById(id) != -1) {
            printf("That ID already exists. Use a different one.\n");
        } else {
            break;
        }
    }

    char name[NAME_LEN];
    char dept[DEPT_LEN];
    readLine("Full name: ", name, sizeof name);
    readLine("Department: ", dept, sizeof dept);

    double basic     = readAmount("Basic salary (N$): ", 0);
    double housing   = readAmount("Housing allowance (N$): ", 1);
    double transport = readAmount("Transport allowance (N$): ", 1);

    empId[empCount] = id;
    strcpy(empName[empCount], name);
    strcpy(empDept[empCount], dept);
    empBasic[empCount]     = basic;
    empHousing[empCount]   = housing;
    empTransport[empCount] = transport;
    empCount++;

    printf("Employee added successfully.\n");
}

void displayEmployees(void)
{
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    printTableHeader();
    for (int i = 0; i < empCount; i++) {
        printEmployeeRow(i);
    }
    printf("\nTotal employees: %d\n", empCount);
}

void searchEmployee(void)
{
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printf("\nSearch by:\n  1. Employee ID\n  2. Name\n");
    int choice = readInt("Choice: ");

    if (choice == 1) {
        int id = readInt("Enter ID: ");
        int idx = findEmployeeById(id);
        if (idx == -1) {
            printf("No employee found with ID %d.\n", id);
        } else {
            printTableHeader();
            printEmployeeRow(idx);
        }
    } else if (choice == 2) {
        char name[NAME_LEN];
        readLine("Enter full name: ", name, sizeof name);
        int found = 0;
        for (int i = 0; i < empCount; i++) {
            if (sameName(empName[i], name)) {
                if (!found) {
                    printTableHeader();
                }
                printEmployeeRow(i);
                found = 1;
            }
        }
        if (!found) {
            printf("No employee found with the name \"%s\".\n", name);
        }
    } else {
        printf("Invalid choice. Enter 1 or 2.\n");
    }
}

void displaySalaryInfo(void)
{
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    int id = readInt("Enter employee ID: ");
    int idx = findEmployeeById(id);
    if (idx == -1) {
        printf("No employee found with ID %d.\n", id);
        return;
    }

    double gross = calculateGrossSalary(empBasic[idx], empHousing[idx], empTransport[idx]);
    double ded   = calculateDeduction(gross);
    double net   = calculateNetSalary(gross, ded);

    printf("\n--- Salary Information ---\n");
    printf("Employee   : %s (ID %d)\n", empName[idx], empId[idx]);
    printf("Department : %s\n", empDept[idx]);
    printf("Basic      : N$%.2f\n", empBasic[idx]);
    printf("Housing    : N$%.2f\n", empHousing[idx]);
    printf("Transport  : N$%.2f\n", empTransport[idx]);
    printf("Gross      : N$%.2f\n", gross);
    printf("Deduction  : N$%.2f (%.0f%%)\n", ded, DEDUCTION_RATE * 100);
    printf("Net salary : N$%.2f\n", net);
}


void employeeMenu(void)
{
    int choice;
    do {
        printf("\n========== EMPLOYEE MANAGEMENT ==========\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search employee\n");
        printf("4. Calculate salary information\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: addEmployee();       break;
            case 2: displayEmployees();  break;
            case 3: searchEmployee();    break;
            case 4: displaySalaryInfo(); break;
            case 5: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Enter a number from 1 to 5.\n");
        }
    } while (choice != 5);
}



int getEmployeeCount(void)
{
    return empCount;
}

double getAverageSalary(void)
{
    if (empCount == 0) {
        return 0.0;
    }
    double total = 0.0;
    for (int i = 0; i < empCount; i++) {
        total += calculateGrossSalary(empBasic[i], empHousing[i], empTransport[i]);
    }
    return total / empCount;
}

double getHighestSalary(void)
{
    if (empCount == 0) {
        return 0.0;
    }
    double max = calculateGrossSalary(empBasic[0], empHousing[0], empTransport[0]);
    for (int i = 1; i < empCount; i++) {
        double g = calculateGrossSalary(empBasic[i], empHousing[i], empTransport[i]);
        if (g > max) {
            max = g;
        }
    }
    return max;
}

double getLowestSalary(void)
{
    if (empCount == 0) {
        return 0.0;
    }
    double min = calculateGrossSalary(empBasic[0], empHousing[0], empTransport[0]);
    for (int i = 1; i < empCount; i++) {
        double g = calculateGrossSalary(empBasic[i], empHousing[i], empTransport[i]);
        if (g < min) {
            min = g;
        }
    }
    return min;
}