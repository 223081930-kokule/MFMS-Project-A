#include <stdio.h>
#include <string.h>
#include "employees.h"

int employeeIDs[MAX_EMPLOYEES];
char employeeNames[MAX_EMPLOYEES][100];
char employeeDepartments[MAX_EMPLOYEES][100];

double basicSalaries[MAX_EMPLOYEES];
double housingAllowances[MAX_EMPLOYEES];
double transportAllowances[MAX_EMPLOYEES];

int employeeCount = 0;

double calculateEmployeeSalary(double basic, double housing, double transport)
{
    return basic + housing + transport;
}

void addEmployee(void)
{
    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Employee limit reached.\n");
        return;
    }

    printf("\n--- ADD EMPLOYEE ---\n");

    printf("Enter employee ID: ");
    scanf("%d", &employeeIDs[employeeCount]);

    printf("Enter employee name: ");
    scanf(" %99[^\n]", employeeNames[employeeCount]);

    printf("Enter department: ");
    scanf(" %99[^\n]", employeeDepartments[employeeCount]);

    printf("Enter basic salary: ");
    scanf("%lf", &basicSalaries[employeeCount]);

    while (basicSalaries[employeeCount] < 0)
    {
        printf("Salary cannot be negative. Enter again: ");
        scanf("%lf", &basicSalaries[employeeCount]);
    }

    printf("Enter housing allowance: ");
    scanf("%lf", &housingAllowances[employeeCount]);

    while (housingAllowances[employeeCount] < 0)
    {
        printf("Allowance cannot be negative. Enter again: ");
        scanf("%lf", &housingAllowances[employeeCount]);
    }

    printf("Enter transport allowance: ");
    scanf("%lf", &transportAllowances[employeeCount]);

    while (transportAllowances[employeeCount] < 0)
    {
        printf("Allowance cannot be negative. Enter again: ");
        scanf("%lf", &transportAllowances[employeeCount]);
    }

    employeeCount++;

    printf("Employee added successfully.\n");
}

void displayEmployees(void)
{
    if (employeeCount == 0)
    {
        printf("\nNo employees have been added yet.\n");
        return;
    }

    printf("\n--- EMPLOYEE LIST ---\n");

    for (int i = 0; i < employeeCount; i++)
    {
        double grossSalary = calculateEmployeeSalary(
            basicSalaries[i],
            housingAllowances[i],
            transportAllowances[i]
        );

        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", employeeIDs[i]);
        printf("Name: %s\n", employeeNames[i]);
        printf("Department: %s\n", employeeDepartments[i]);
        printf("Basic Salary: %.2f\n", basicSalaries[i]);
        printf("Housing Allowance: %.2f\n", housingAllowances[i]);
        printf("Transport Allowance: %.2f\n", transportAllowances[i]);
        printf("Gross Salary: %.2f\n", grossSalary);
    }
}

void searchEmployee(void)
{
    int searchID;
    int found = 0;

    if (employeeCount == 0)
    {
        printf("\nNo employees have been added yet.\n");
        return;
    }

    printf("\nEnter employee ID to search: ");
    scanf("%d", &searchID);

    for (int i = 0; i < employeeCount; i++)
    {
        if (employeeIDs[i] == searchID)
        {
            double grossSalary = calculateEmployeeSalary(
                basicSalaries[i],
                housingAllowances[i],
                transportAllowances[i]
            );

            printf("\n--- EMPLOYEE FOUND ---\n");
            printf("ID: %d\n", employeeIDs[i]);
            printf("Name: %s\n", employeeNames[i]);
            printf("Department: %s\n", employeeDepartments[i]);
            printf("Gross Salary: %.2f\n", grossSalary);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Employee not found.\n");
    }
}

void employeeReport(void)
{
    double totalSalary = 0;
    double highestSalary = 0;
    double lowestSalary = 0;

    if (employeeCount == 0)
    {
        printf("\nNo employees available for report.\n");
        return;
    }

    for (int i = 0; i < employeeCount; i++)
    {
        double salary = calculateEmployeeSalary(
            basicSalaries[i],
            housingAllowances[i],
            transportAllowances[i]
        );

        totalSalary += salary;

        if (i == 0)
        {
            highestSalary = salary;
            lowestSalary = salary;
        }
        else
        {
            if (salary > highestSalary)
            {
                highestSalary = salary;
            }

            if (salary < lowestSalary)
            {
                lowestSalary = salary;
            }
        }
    }

    printf("\n--- EMPLOYEE REPORT ---\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Total Salary: %.2f\n", totalSalary);
    printf("Average Salary: %.2f\n", totalSalary / employeeCount);
    printf("Highest Salary: %.2f\n", highestSalary);
    printf("Lowest Salary: %.2f\n", lowestSalary);
}