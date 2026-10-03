/* reports.c - Reports module (Student 5) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"

/* ---------- helper functions ---------- */

static void printLine(char c, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(c);
    putchar('\n');
}

static void printHeading(const char *title)
{
    printLine('=', 60);
    printf("%s\n", title);
    printLine('=', 60);
}

/* Reads a whole line and validates it as an integer in [min, max].
 * Keeps asking until the input is valid. */
static int readMenuChoice(int min, int max)
{
    char buf[64];
    char *end;
    long value;

    while (1) {
        printf("Enter your choice: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            return max;                      /* EOF: leave the menu */
        value = strtol(buf, &end, 10);
        if (end != buf && (*end == '\n' || *end == '\0')
            && value >= min && value <= max)
            return (int)value;
        printf("Invalid choice. Enter a number from %d to %d.\n", min, max);
    }
}

/* ---------- 1. Employee report ---------- */

void employeeReport(char names[][STR_LEN], char depts[][STR_LEN],
                    double salaries[], int count)
{
    int i, maxIdx = 0, minIdx = 0;
    double total = 0.0;
    char highName[STR_LEN], lowName[STR_LEN];

    printHeading("EMPLOYEE REPORT");

    if (count <= 0) {
        printf("No employees registered yet.\n\n");
        return;
    }

    for (i = 0; i < count; i++) {
        total += salaries[i];
        if (salaries[i] > salaries[maxIdx]) maxIdx = i;
        if (salaries[i] < salaries[minIdx]) minIdx = i;
    }

    strcpy(highName, names[maxIdx]);
    strcpy(lowName, names[minIdx]);

    printf("Total Employees: %d\n", count);
    printf("Average Salary : N$%.2f\n", total / count);
    printf("Highest Salary : N$%.2f (%s, %s)\n", salaries[maxIdx],
           highName, depts[maxIdx]);
    printf("Lowest Salary  : N$%.2f (%s, %s)\n\n", salaries[minIdx],
           lowName, depts[minIdx]);
}

/* ---------- 2. Budget report ---------- */

void budgetReport(char depts[][STR_LEN], double allocated[],
                  double spent[], int count)
{
    int i, exceeded = 0;
    double totalAlloc = 0.0, totalSpent = 0.0;

    printHeading("BUDGET REPORT");

    if (count <= 0) {
        printf("No department budgets entered yet.\n\n");
        return;
    }

    for (i = 0; i < count; i++) {
        totalAlloc += allocated[i];
        totalSpent += spent[i];
    }

    printf("Total Allocated Budget: N$%.2f\n", totalAlloc);
    printf("Total Expenditure     : N$%.2f\n", totalSpent);
    printf("Remaining Budget      : N$%.2f\n\n", totalAlloc - totalSpent);

    printf("Departments exceeding budget:\n");
    for (i = 0; i < count; i++) {
        if (spent[i] > allocated[i]) {
            printf("  - %-20s Allocated: N$%.2f  Spent: N$%.2f  "
                   "Over by: N$%.2f\n", depts[i], allocated[i], spent[i],
                   spent[i] - allocated[i]);
            exceeded++;
        }
    }
    if (exceeded == 0)
        printf("  None - all departments are within budget.\n");
    printf("\n");
}

/* ---------- 3. Supplier report ---------- */

void supplierReport(int ids[], char names[][STR_LEN], char emails[][STR_LEN],
                    char phones[][STR_LEN], char towns[][STR_LEN], int count)
{
    int i;

    printHeading("SUPPLIER REPORT");

    if (count <= 0) {
        printf("No suppliers registered yet.\n\n");
        return;
    }

    printf("%-5s %-20s %-25s %-14s %-12s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 80);
    for (i = 0; i < count; i++)
        printf("%-5d %-20s %-25s %-14s %-12s\n",
               ids[i], names[i], emails[i], phones[i], towns[i]);
    printf("\nTotal Suppliers: %d\n\n", count);
}

/* ---------- 4. Asset report ---------- */

void assetReport(int ids[], char names[][STR_LEN], char types[][STR_LEN],
                 double values[], char depts[][STR_LEN],
                 char conditions[][STR_LEN], int count)
{
    int i, poorCount = 0;
    double totalValue = 0.0;

    printHeading("ASSET REPORT");

    if (count <= 0) {
        printf("No assets registered yet.\n\n");
        return;
    }

    printf("%-5s %-18s %-12s %-13s %-14s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine('-', 76);
    for (i = 0; i < count; i++) {
        printf("%-5d %-18s %-12s %-13.2f %-14s %-10s\n",
               ids[i], names[i], types[i], values[i], depts[i],
               conditions[i]);
        totalValue += values[i];
        if (strcmp(conditions[i], "Poor") == 0)
            poorCount++;
    }
    printf("\nTotal Assets      : %d\n", count);
    printf("Total Asset Value : N$%.2f\n", totalValue);
    printf("Assets in Poor condition: %d\n\n", poorCount);
}

/* ---------- Reports sub-menu ---------- */

void displayReports(
    char empNames[][STR_LEN], char empDepts[][STR_LEN],
    double empSalaries[], int empCount,
    char budDepts[][STR_LEN], double budAllocated[], double budSpent[],
    int budCount,
    int supIds[], char supNames[][STR_LEN], char supEmails[][STR_LEN],
    char supPhones[][STR_LEN], char supTowns[][STR_LEN], int supCount,
    int assetIds[], char assetNames[][STR_LEN], char assetTypes[][STR_LEN],
    double assetValues[], char assetDepts[][STR_LEN],
    char assetConds[][STR_LEN], int assetCount)
{
    int choice;

    do {
        printf("\n");
        printLine('=', 40);
        printf("               REPORTS\n");
        printLine('=', 40);
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");

        choice = readMenuChoice(1, 5);
        printf("\n");

        switch (choice) {
        case 1:
            employeeReport(empNames, empDepts, empSalaries, empCount);
            break;
        case 2:
            budgetReport(budDepts, budAllocated, budSpent, budCount);
            break;
        case 3:
            supplierReport(supIds, supNames, supEmails, supPhones,
                           supTowns, supCount);
            break;
        case 4:
            assetReport(assetIds, assetNames, assetTypes, assetValues,
                        assetDepts, assetConds, assetCount);
            break;
        case 5:
            break;
        }
    } while (choice != 5);
}
