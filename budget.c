#include <stdio.h>
#include <string.h>
#include "budget.h"

char departmentNames[MAX_DEPARTMENTS][100];
double allocatedBudgets[MAX_DEPARTMENTS];
double expenditures[MAX_DEPARTMENTS];

int budgetCount = 0;

double calculateBudget(double budget, double expenditure)
{
    return budget - expenditure;
}

void addBudget(void)
{
    if (budgetCount >= MAX_DEPARTMENTS)
    {
        printf("Department limit reached.\n");
        return;
    }

    printf("\n--- ADD DEPARTMENT BUDGET ---\n");

    printf("Enter department name: ");
    scanf(" %99[^\n]", departmentNames[budgetCount]);

    printf("Enter allocated budget: ");
    scanf("%lf", &allocatedBudgets[budgetCount]);

    while (allocatedBudgets[budgetCount] < 0)
    {
        printf("Budget cannot be negative. Enter again: ");
        scanf("%lf", &allocatedBudgets[budgetCount]);
    }

    printf("Enter expenditure: ");
    scanf("%lf", &expenditures[budgetCount]);

    while (expenditures[budgetCount] < 0)
    {
        printf("Expenditure cannot be negative. Enter again: ");
        scanf("%lf", &expenditures[budgetCount]);
    }

    budgetCount++;

    printf("Budget added successfully.\n");
}

void displayBudgets(void)
{
    if (budgetCount == 0)
    {
        printf("\nNo budgets have been added yet.\n");
        return;
    }

    printf("\n--- DEPARTMENT BUDGETS ---\n");

    for (int i = 0; i < budgetCount; i++)
    {
        double remaining = calculateBudget(
            allocatedBudgets[i],
            expenditures[i]
        );

        printf("\nDepartment: %s\n", departmentNames[i]);
        printf("Allocated Budget: %.2f\n", allocatedBudgets[i]);
        printf("Expenditure: %.2f\n", expenditures[i]);
        printf("Remaining Budget: %.2f\n", remaining);

        if (remaining >= 0)
        {
            printf("Status: Within Budget\n");
        }
        else
        {
            printf("Status: Over Budget\n");
        }
    }
}

void searchBudget(void)
{
    char searchName[100];
    int found = 0;

    if (budgetCount == 0)
    {
        printf("\nNo budgets have been added yet.\n");
        return;
    }

    printf("\nEnter department to search: ");
    scanf(" %99[^\n]", searchName);

    for (int i = 0; i < budgetCount; i++)
    {
        if (strcmp(departmentNames[i], searchName) == 0)
        {
            double remaining = calculateBudget(
                allocatedBudgets[i],
                expenditures[i]
            );

            printf("\n--- BUDGET FOUND ---\n");
            printf("Department: %s\n", departmentNames[i]);
            printf("Allocated Budget: %.2f\n", allocatedBudgets[i]);
            printf("Expenditure: %.2f\n", expenditures[i]);
            printf("Remaining Budget: %.2f\n", remaining);

            if (remaining >= 0)
            {
                printf("Status: Within Budget\n");
            }
            else
            {
                printf("Status: Over Budget\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Department budget not found.\n");
    }
}

void budgetReport(void)
{
    double totalAllocated = 0;
    double totalExpenditure = 0;
    int departmentsOverBudget = 0;

    if (budgetCount == 0)
    {
        printf("\nNo budgets available for report.\n");
        return;
    }

    for (int i = 0; i < budgetCount; i++)
    {
        totalAllocated += allocatedBudgets[i];
        totalExpenditure += expenditures[i];

        if (expenditures[i] > allocatedBudgets[i])
        {
            departmentsOverBudget++;
        }
    }

    double totalRemaining = totalAllocated - totalExpenditure;

    printf("\n--- BUDGET REPORT ---\n");
    printf("Total Allocated: %.2f\n", totalAllocated);
    printf("Total Expenditure: %.2f\n", totalExpenditure);
    printf("Total Remaining: %.2f\n", totalRemaining);
    printf("Departments Over Budget: %d\n", departmentsOverBudget);
}