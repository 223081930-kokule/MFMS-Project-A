#include <stdio.h>
#include <string.h>
#include "suppliers.h"

void addSupplier(Supplier suppliers[], int *supplierCount)
{
    int id;
    int duplicate;

    if (*supplierCount >= MAX_SUPPLIERS)
    {
        printf("\nSupplier storage is full.\n");
        return;
    }

    printf("\n========== ADD SUPPLIER ==========\n");

    do
    {
        printf("Enter Supplier ID: ");
        scanf("%d", &id);

        if (id <= 0)
        {
            printf("Supplier ID must be greater than 0.\n");
        }

    } while (id <= 0);

    duplicate = 0;

    for (int i = 0; i < *supplierCount; i++)
    {
        if (suppliers[i].id == id)
        {
            duplicate = 1;
            break;
        }
    }

    if (duplicate)
    {
        printf("A supplier with that ID already exists.\n");
        return;
    }

    suppliers[*supplierCount].id = id;

    getchar();

    do
    {
        printf("Enter Supplier Name: ");
        fgets(suppliers[*supplierCount].name,
              sizeof(suppliers[*supplierCount].name),
              stdin);

        suppliers[*supplierCount].name[
            strcspn(suppliers[*supplierCount].name, "\n")
        ] = '\0';

        if (strlen(suppliers[*supplierCount].name) == 0)
        {
            printf("Supplier name cannot be empty.\n");
        }

    } while (strlen(suppliers[*supplierCount].name) == 0);

    do
    {
        printf("Enter Email: ");
        fgets(suppliers[*supplierCount].email,
              sizeof(suppliers[*supplierCount].email),
              stdin);

        suppliers[*supplierCount].email[
            strcspn(suppliers[*supplierCount].email, "\n")
        ] = '\0';

        if (strlen(suppliers[*supplierCount].email) == 0)
        {
            printf("Email cannot be empty.\n");
        }

    } while (strlen(suppliers[*supplierCount].email) == 0);

    do
    {
        printf("Enter Telephone Number: ");
        fgets(suppliers[*supplierCount].telephone,
              sizeof(suppliers[*supplierCount].telephone),
              stdin);

        suppliers[*supplierCount].telephone[
            strcspn(suppliers[*supplierCount].telephone, "\n")
        ] = '\0';

        if (strlen(suppliers[*supplierCount].telephone) == 0)
        {
            printf("Telephone number cannot be empty.\n");
        }

    } while (strlen(suppliers[*supplierCount].telephone) == 0);

    do
    {
        printf("Enter Town/Location: ");
        fgets(suppliers[*supplierCount].town,
              sizeof(suppliers[*supplierCount].town),
              stdin);

        suppliers[*supplierCount].town[
            strcspn(suppliers[*supplierCount].town, "\n")
        ] = '\0';

        if (strlen(suppliers[*supplierCount].town) == 0)
        {
            printf("Town/Location cannot be empty.\n");
        }

    } while (strlen(suppliers[*supplierCount].town) == 0);

    (*supplierCount)++;

    printf("\nSupplier added successfully!\n");
}

void displaySuppliers(Supplier suppliers[], int supplierCount)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers have been registered.\n");
        return;
    }

    printf("\n================ SUPPLIER LIST ================\n");

    for (int i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier %d\n", i + 1);
        printf("ID        : %d\n", suppliers[i].id);
        printf("Name      : %s\n", suppliers[i].name);
        printf("Email     : %s\n", suppliers[i].email);
        printf("Telephone : %s\n", suppliers[i].telephone);
        printf("Town      : %s\n", suppliers[i].town);
    }
}

void searchSupplier(Supplier suppliers[], int supplierCount)
{
    int choice;
    int id;
    char name[50];
    int found = 0;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers have been registered.\n");
        return;
    }

    printf("\n========== SEARCH SUPPLIER ==========\n");
    printf("1. Search by Supplier ID\n");
    printf("2. Search by Supplier Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter Supplier ID: ");
        scanf("%d", &id);

        for (int i = 0; i < supplierCount; i++)
        {
            if (suppliers[i].id == id)
            {
                printf("\nSupplier found!\n");
                printf("ID        : %d\n", suppliers[i].id);
                printf("Name      : %s\n", suppliers[i].name);
                printf("Email     : %s\n", suppliers[i].email);
                printf("Telephone : %s\n", suppliers[i].telephone);
                printf("Town      : %s\n", suppliers[i].town);

                found = 1;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        getchar();

        printf("Enter Supplier Name: ");
        fgets(name, sizeof(name), stdin);

        name[strcspn(name, "\n")] = '\0';

        for (int i = 0; i < supplierCount; i++)
        {
            if (strcmp(suppliers[i].name, name) == 0)
            {
                printf("\nSupplier found!\n");
                printf("ID        : %d\n", suppliers[i].id);
                printf("Name      : %s\n", suppliers[i].name);
                printf("Email     : %s\n", suppliers[i].email);
                printf("Telephone : %s\n", suppliers[i].telephone);
                printf("Town      : %s\n", suppliers[i].town);

                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("Invalid search choice.\n");
        return;
    }

    if (!found)
    {
        printf("\nSupplier not found.\n");
    }
}
