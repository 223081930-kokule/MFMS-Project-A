/*
 * budget.c - Budget Management module (MFMS Project A)
 * Stores departmental budgets in parallel arrays: index i in every
 * array refers to the same department.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"

static char   deptNames[MAX_DEPARTMENTS][DEPT_NAME_LEN];
static double allocated[MAX_DEPARTMENTS];
static double expenditure[MAX_DEPARTMENTS];
static int    deptCount = 0;

/* ---------- input helpers ---------- */

/* Prints a prompt and reads one line safely (no buffer overflow). */
static void readLine(const char *prompt, char *buf, int size)
{
    size_t len;
    int c;

    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nInput ended. Exiting.\n");
        exit(1);
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        /* line was longer than the buffer: throw away the rest */
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}

/* Keeps asking until the user enters a valid number that is >= 0. */
static double readAmount(const char *prompt)
{
    char buf[64];
    char *end;
    double value;

    while (1) {
        readLine(prompt, buf, (int)sizeof buf);
        value = strtod(buf, &end);
        while (*end == ' ') {
            end++;
        }
        if (end == buf || *end != '\0') {
            printf("Invalid number. Please enter digits only.\n");
        } else if (value < 0) {
            printf("Amount cannot be negative.\n");
        } else {
            return value;
        }
    }
}

/* Keeps asking until the user enters a non-empty name. */
static void readDepartmentName(char *name, int size)
{
    while (1) {
        readLine("Department name: ", name, size);
        if (strlen(name) == 0) {
            printf("Department name cannot be empty.\n");
        } else {
            return;
        }
    }
}

/* ---------- search / calculation ---------- */

/* Returns the index of the department, or -1 if it is not found. */
static int findDepartment(const char *name)
{
    int i;
    for (i = 0; i < deptCount; i++) {
        if (strcmp(deptNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

double calculateRemaining(double allocatedAmt, double spent)
{
    return allocatedAmt - spent;
}

int isWithinBudget(double allocatedAmt, double spent)
{
    return spent <= allocatedAmt;   /* 1 = within budget, 0 = exceeded */
}

/* ---------- operations ---------- */

void addDepartmentBudget(void)
{
    char name[DEPT_NAME_LEN];
    double amount;

    if (deptCount >= MAX_DEPARTMENTS) {
        printf("Department list is full (%d max).\n", MAX_DEPARTMENTS);
        return;
    }

    readDepartmentName(name, DEPT_NAME_LEN);
    if (findDepartment(name) != -1) {
        printf("That department already has a budget.\n");
        return;
    }

    amount = readAmount("Allocated budget (N$): ");

    strcpy(deptNames[deptCount], name);
    allocated[deptCount] = amount;
    expenditure[deptCount] = 0.0;
    deptCount++;
    printf("Budget added for %s.\n", name);
}

void recordExpenditure(void)
{
    char name[DEPT_NAME_LEN];
    int idx;
    double amount;

    if (deptCount == 0) {
        printf("No departments yet. Add a budget first.\n");
        return;
    }

    readDepartmentName(name, DEPT_NAME_LEN);
    idx = findDepartment(name);
    if (idx == -1) {
        printf("Department not found.\n");
        return;
    }

    amount = readAmount("Expenditure to record (N$): ");
    expenditure[idx] += amount;   /* adds to what was already spent */
    printf("Expenditure recorded. Total spent by %s: N$%.2f\n",
           deptNames[idx], expenditure[idx]);
}

void displayBudgets(void)
{
    int i;
    double remaining;

    if (deptCount == 0) {
        printf("No budget information to display.\n");
        return;
    }

    for (i = 0; i < deptCount; i++) {
        remaining = calculateRemaining(allocated[i], expenditure[i]);
        printf("\nDepartment: %s\n", deptNames[i]);
        printf("Allocated Budget: N$%.2f\n", allocated[i]);
        printf("Expenditure: N$%.2f\n", expenditure[i]);
        printf("Remaining Budget: N$%.2f\n", remaining);
        printf("Status: %s\n",
               isWithinBudget(allocated[i], expenditure[i])
                   ? "WITHIN BUDGET" : "EXCEEDED BUDGET");
    }
}

void displayExceededDepartments(void)
{
    int i;
    int found = 0;

    printf("\nDepartments exceeding budget:\n");
    for (i = 0; i < deptCount; i++) {
        if (!isWithinBudget(allocated[i], expenditure[i])) {
            printf(" - %s (over by N$%.2f)\n", deptNames[i],
                   expenditure[i] - allocated[i]);
            found = 1;
        }
    }
    if (!found) {
        printf(" None.\n");
    }
}

void displayBudgetReport(void)
{
    int i;
    double totalAllocated = 0.0;
    double totalSpent = 0.0;

    for (i = 0; i < deptCount; i++) {
        totalAllocated += allocated[i];
        totalSpent += expenditure[i];
    }

    printf("\n===== BUDGET REPORT =====\n");
    printf("Departments: %d\n", deptCount);
    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalSpent);
    printf("Total Remaining Budget: N$%.2f\n",
           calculateRemaining(totalAllocated, totalSpent));
    displayExceededDepartments();
}

void budgetMenu(void)
{
    char buf[16];
    char *end;
    long choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add department budget\n");
        printf("2. Record expenditure\n");
        printf("3. Display budgets\n");
        printf("4. Show departments over budget\n");
        printf("5. Budget report\n");
        printf("6. Back to main menu\n");
        readLine("Enter your choice: ", buf, (int)sizeof buf);

        choice = strtol(buf, &end, 10);
        if (end == buf || *end != '\0') {
            choice = 0;   /* not a number: falls into default below */
        }

        switch (choice) {
            case 1: addDepartmentBudget();       break;
            case 2: recordExpenditure();         break;
            case 3: displayBudgets();            break;
            case 4: displayExceededDepartments(); break;
            case 5: displayBudgetReport();       break;
            case 6: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Enter 1-6.\n");
        }
    } while (choice != 6);
}
