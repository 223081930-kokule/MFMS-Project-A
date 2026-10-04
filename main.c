#include <stdio.h>

#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

/* ---------- Function Prototypes ---------- */

void displayMenu(void);
void clearInputBuffer(void);

/* ---------- Main Menu ---------- */

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
}

/* ---------- Input Validation ---------- */

void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
        /* Clear invalid input */
    }
}

/* ---------- Main Program ---------- */

int main(void)
{
    int choice;

    /* Supplier data is managed by main.c */
    Supplier suppliers[MAX_SUPPLIERS];
    int supplierCount = 0;

    do
    {
        displayMenu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number from 1 to 6.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;

            case 2:
                budgetMenu();
                break;

            case 3:
            {
                int supplierChoice;

                do
                {
                    printf("\n");
                    printf("========================================\n");
                    printf("        SUPPLIER MANAGEMENT\n");
                    printf("========================================\n");
                    printf("1. Add Supplier\n");
                    printf("2. Display Suppliers\n");
                    printf("3. Search Supplier\n");
                    printf("4. Back to Main Menu\n");
                    printf("========================================\n");
                    printf("Enter your choice: ");

                    if (scanf("%d", &supplierChoice) != 1)
                    {
                        printf("Invalid input. Please enter a number.\n");
                        clearInputBuffer();
                        continue;
                    }

                    switch (supplierChoice)
                    {
                        case 1:
                            addSupplier(suppliers, &supplierCount);
                            break;

                        case 2:
                            displaySuppliers(suppliers, supplierCount);
                            break;

                        case 3:
                            searchSupplier(suppliers, supplierCount);
                            break;

                        case 4:
                            printf("Returning to main menu...\n");
                            break;

                        default:
                            printf("Invalid choice. Please select 1 to 4.\n");
                    }

                } while (supplierChoice != 4);

                break;
            }

            case 4:
            {
                int assetChoice;

                do
                {
                    printf("\n");
                    printf("========================================\n");
                    printf("          ASSET MANAGEMENT\n");
                    printf("========================================\n");
                    printf("1. Add Asset\n");
                    printf("2. Display Assets\n");
                    printf("3. Search Asset\n");
                    printf("4. Asset Report\n");
                    printf("5. Back to Main Menu\n");
                    printf("========================================\n");
                    printf("Enter your choice: ");

                    if (scanf("%d", &assetChoice) != 1)
                    {
                        printf("Invalid input. Please enter a number.\n");
                        clearInputBuffer();
                        continue;
                    }

                    switch (assetChoice)
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

                        case 5:
                            printf("Returning to main menu...\n");
                            break;

                        default:
                            printf("Invalid choice. Please select 1 to 5.\n");
                    }

                } while (assetChoice != 5);

                break;
            }

            case 5:
                displayReports(suppliers, supplierCount);
                break;

            case 6:
                printf("\n");
                printf("Thank you for using the Municipal Financial Management System.\n");
                break;

            default:
                printf("\nInvalid choice. Please select 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}