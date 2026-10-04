#include <stdio.h>

#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

/* Function prototypes */
void displayMenu(void);
void clearInputBuffer(void);

void displayMenu(void)
{
    printf("\n");
    printf("========================================\n");
    printf("   MUNICIPAL FINANCIAL MANAGEMENT\n");
    printf("              SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
        /* Clear invalid input */
    }
}

int main(void)
{
    int choice;

    do
    {
        displayMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number from 1 to 6.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("\n--- EMPLOYEE MANAGEMENT ---\n");
                printf("1. Add Employee\n");
                printf("2. Display Employees\n");
                printf("3. Search Employee\n");
                printf("4. Employee Report\n");
                printf("Enter choice: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Invalid input.\n");
                    clearInputBuffer();
                    break;
                }

                switch (choice)
                {
                    case 1:
                        addEmployee();
                        break;

                    case 2:
                        displayEmployees();
                        break;

                    case 3:
                        searchEmployee();
                        break;

                    case 4:
                        employeeReport();
                        break;

                    default:
                        printf("Invalid employee menu choice.\n");
                }
                break;

            case 2:
                printf("\n--- BUDGET MANAGEMENT ---\n");
                printf("1. Add Budget\n");
                printf("2. Display Budgets\n");
                printf("3. Search Budget\n");
                printf("4. Budget Report\n");
                printf("Enter choice: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Invalid input.\n");
                    clearInputBuffer();
                    break;
                }

                switch (choice)
                {
                    case 1:
                        addBudget();
                        break;

                    case 2:
                        displayBudgets();
                        break;

                    case 3:
                        searchBudget();
                        break;

                    case 4:
                        budgetReport();
                        break;

                    default:
                        printf("Invalid budget menu choice.\n");
                }
                break;

            case 3:
                printf("\n--- SUPPLIER MANAGEMENT ---\n");
                printf("1. Add Supplier\n");
                printf("2. Display Suppliers\n");
                printf("3. Search Supplier\n");
                printf("4. Supplier Report\n");
                printf("Enter choice: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Invalid input.\n");
                    clearInputBuffer();
                    break;
                }

                switch (choice)
                {
                    case 1:
                        addSupplier();
                        break;

                    case 2:
                        displaySuppliers();
                        break;

                    case 3:
                        searchSupplier();
                        break;

                    case 4:
                        supplierReport();
                        break;

                    default:
                        printf("Invalid supplier menu choice.\n");
                }
                break;

            case 4:
                printf("\n--- ASSET MANAGEMENT ---\n");
                printf("1. Add Asset\n");
                printf("2. Display Assets\n");
                printf("3. Search Asset\n");
                printf("4. Asset Report\n");
                printf("Enter choice: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Invalid input.\n");
                    clearInputBuffer();
                    break;
                }

                switch (choice)
                {
                    case 1:
                        addAsset();
                        break;

                    case 2:
                        displayAssets();
                        break;

                    case 3:
                        searchAsset();
                        break;

                    case 4:
                        assetReport();
                        break;

                    default:
                        printf("Invalid asset menu choice.\n");
                }
                break;

            case 5:
                displayAllReports();
                break;

            case 6:
                printf("\nThank you for using the Municipal Financial Management System.\n");
                break;

            default:
                printf("\nInvalid choice. Please select 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}