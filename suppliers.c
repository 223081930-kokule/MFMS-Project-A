#include <stdio.h>
#include <string.h>
#include "suppliers.h"
int supplierIDs[MAX_SUPPLIERS];
char supplierNames[MAX_SUPPLIERS][100];
char supplierEmails[MAX_SUPPLIERS][100];
char supplierPhones[MAX_SUPPLIERS][30];
char supplierTowns[MAX_SUPPLIERS][50];
int supplierCount = 0;
void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("Supplier limit reached.\n");
        return;
    }
    printf("\n--- ADD SUPPLIER ---\n");
    printf("Enter supplier ID: ");
    scanf("%d", &supplierIDs[supplierCount]);
    printf("Enter supplier name: ");
    scanf(" %99[^\n]", supplierNames[supplierCount]);
    printf("Enter supplier email: ");
    scanf(" %99[^\n]", supplierEmails[supplierCount]);
    printf("Enter supplier telephone: ");
    scanf(" %29[^\n]", supplierPhones[supplierCount]);
    printf("Enter supplier town/location: ");
    scanf(" %49[^\n]", supplierTowns[supplierCount]);
    supplierCount++;
    printf("Supplier added successfully.\n");
}
void displaySuppliers(void)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers have been added yet.\n");
        return;
    }
    printf("\n--- SUPPLIER LIST ---\n");
    for (int i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier %d\n", i + 1);
        printf("ID: %d\n", supplierIDs[i]);
        printf("Name: %s\n", supplierNames[i]);
        printf("Email: %s\n", supplierEmails[i]);
        printf("Telephone: %s\n", supplierPhones[i]);
        printf("Town/Location: %s\n", supplierTowns[i]);
        printf("Supplier name length: %zu characters\n",
               strlen(supplierNames[i]));
    }
}
void searchSupplier(void)
{
    char searchName[100];
    int found = 0;
    if (supplierCount == 0)
    {
        printf("\nNo suppliers have been added yet.\n");
        return;
    }
    printf("\nEnter supplier name to search: ");
    scanf(" %99[^\n]", searchName);
    for (int i = 0; i < supplierCount; i++)
    {
        if (strcmp(supplierNames[i], searchName) == 0)
        {
            char supplierDescription[250] = "";
            strcpy(supplierDescription, supplierNames[i]);
            strcat(supplierDescription, " - ");
            strcat(supplierDescription, supplierTowns[i]);
            printf("\n--- SUPPLIER FOUND ---\n");
            printf("ID: %d\n", supplierIDs[i]);
            printf("Name: %s\n", supplierNames[i]);
            printf("Email: %s\n", supplierEmails[i]);
            printf("Telephone: %s\n", supplierPhones[i]);
            printf("Town/Location: %s\n", supplierTowns[i]);
            printf("Description: %s\n", supplierDescription);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Supplier not found.\n");
    }
}
void supplierReport(void)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers available for report.\n");
        return;
    }
    printf("\n--- SUPPLIER REPORT ---\n");
    printf("Total Suppliers: %d\n", supplierCount);
    for (int i = 0; i < supplierCount; i++)
    {
        printf("%d. %s - %s\n",
               supplierIDs[i],
               supplierNames[i],
               supplierTowns[i]);
    }
}
