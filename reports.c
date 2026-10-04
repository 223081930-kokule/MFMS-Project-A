#include <stdio.h>
#include <string.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "assets.h"

/* ---------- Helper functions ---------- */

static void printLine(char c, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        putchar(c);
    }

    putchar('\n');
}

static void printHeading(const char *title)
{
    printLine('=', 60);
    printf("%s\n", title);
    printLine('=', 60);
}

/* ---------- Employee Report ---------- */

void reportEmployee(void)
{
    printHeading("EMPLOYEE REPORT");

    if (getEmployeeCount() == 0)
    {
        printf("No employees registered yet.\n\n");
        return;
    }

    printf("Total Employees : %d\n", getEmployeeCount());
    printf("Average Salary  : N$%.2f\n", getAverageSalary());
    printf("Highest Salary  : N$%.2f\n", getHighestSalary());
    printf("Lowest Salary   : N$%.2f\n\n", getLowestSalary());
}

/* ---------- Budget Report ---------- */

void reportBudget(void)
{
    printHeading("BUDGET REPORT");

    /*
     * The Budget module already calculates and displays
     * the complete budget report.
     */
    displayBudgetReport();
}

/* ---------- Supplier Report ---------- */

void reportSupplier(Supplier suppliers[], int supplierCount)
{
    int i;

    printHeading("SUPPLIER REPORT");

    if (supplierCount == 0)
    {
        printf("No suppliers registered yet.\n\n");
        return;
    }

    printf("%-5s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Telephone", "Town");

    printLine('-', 85);

    for (i = 0; i < supplierCount; i++)
    {
        printf("%-5d %-20s %-25s %-15s %-15s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].telephone,
               suppliers[i].town);
    }

    printf("\nTotal Suppliers: %d\n\n", supplierCount);
}

/* ---------- Asset Report ---------- */

void assetReport(void)
{
    Asset asset;
    FILE *file;
    int count = 0;
    int vehicles = 0;
    float total = 0.0f;

    printHeading("ASSET REPORT");

    file = fopen("assets.txt", "r");
    if (file == NULL)
    {
        printf("No asset records found.\n\n");
        return;
    }

    printf("%-5s %-20s %-15s %-12s %-12s\n",
           "ID", "Name", "Category", "Value (N$)", "Date");
    printLine('-', 68);

    while (fscanf(file, "%d %49s %29s %f %14s",
                  &asset.assetID, asset.assetName, asset.category,
                  &asset.value, asset.purchaseDate) == 5)
    {
        printf("%-5d %-20s %-15s %-12.2f %-12s\n",
               asset.assetID, asset.assetName, asset.category,
               asset.value, asset.purchaseDate);
        total += asset.value;
        count++;

        if (strcmp(asset.category, "Vehicle") == 0)
        {
            vehicles++;
        }
    }
    fclose(file);

    if (count == 0)
    {
        printf("No asset records found.\n\n");
        return;
    }

    printf("\nTotal Assets      : %d\n", count);
    printf("Total Asset Value : N$%.2f\n", total);
    printf("Vehicles          : %d\n\n", vehicles);
}

void reportAsset(void)
{
    assetReport();
}

/* ---------- Reports Menu ---------- */

void displayReports(Supplier suppliers[], int supplierCount)
{
    int choice;

    do
    {
        printf("\n");
        printLine('=', 40);
        printf("               REPORTS\n");
        printLine('=', 40);

        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number from 1 to 5.\n");

            while (getchar() != '\n')
            {
                /* Clear invalid input */
            }

            continue;
        }

        switch (choice)
        {
            case 1:
                reportEmployee();
                break;

            case 2:
                reportBudget();
                break;

            case 3:
                reportSupplier(suppliers, supplierCount);
                break;

            case 4:
                reportAsset();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Please select 1 to 5.\n");
        }

    } while (choice != 5);
}
