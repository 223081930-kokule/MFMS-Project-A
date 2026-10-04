#include <stdio.h>
#include <string.h>
#include "assets.h"

int assetIDs[MAX_ASSETS];
char assetNames[MAX_ASSETS][100];
char assetTypes[MAX_ASSETS][100];
double purchaseValues[MAX_ASSETS];
char assetDepartments[MAX_ASSETS][100];
char assetConditions[MAX_ASSETS][50];

int assetCount = 0;

void addAsset(void)
{
    if (assetCount >= MAX_ASSETS)
    {
        printf("Asset limit reached.\n");
        return;
    }

    printf("\n--- ADD ASSET ---\n");

    printf("Enter asset ID: ");
    scanf("%d", &assetIDs[assetCount]);

    printf("Enter asset name: ");
    scanf(" %99[^\n]", assetNames[assetCount]);

    printf("Enter asset type: ");
    scanf(" %99[^\n]", assetTypes[assetCount]);

    printf("Enter purchase value: ");
    scanf("%lf", &purchaseValues[assetCount]);

    while (purchaseValues[assetCount] < 0)
    {
        printf("Purchase value cannot be negative. Enter again: ");
        scanf("%lf", &purchaseValues[assetCount]);
    }

    printf("Enter department: ");
    scanf(" %99[^\n]", assetDepartments[assetCount]);

    printf("Enter condition: ");
    scanf(" %49[^\n]", assetConditions[assetCount]);

    assetCount++;

    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    if (assetCount == 0)
    {
        printf("\nNo assets have been added yet.\n");
        return;
    }

    printf("\n--- ASSET LIST ---\n");

    for (int i = 0; i < assetCount; i++)
    {
        printf("\nAsset %d\n", i + 1);
        printf("ID: %d\n", assetIDs[i]);
        printf("Name: %s\n", assetNames[i]);
        printf("Type: %s\n", assetTypes[i]);
        printf("Purchase Value: %.2f\n", purchaseValues[i]);
        printf("Department: %s\n", assetDepartments[i]);
        printf("Condition: %s\n", assetConditions[i]);
    }
}

void searchAsset(void)
{
    int searchID;
    int found = 0;

    if (assetCount == 0)
    {
        printf("\nNo assets have been added yet.\n");
        return;
    }

    printf("\nEnter asset ID to search: ");
    scanf("%d", &searchID);

    for (int i = 0; i < assetCount; i++)
    {
        if (assetIDs[i] == searchID)
        {
            printf("\n--- ASSET FOUND ---\n");
            printf("ID: %d\n", assetIDs[i]);
            printf("Name: %s\n", assetNames[i]);
            printf("Type: %s\n", assetTypes[i]);
            printf("Purchase Value: %.2f\n", purchaseValues[i]);
            printf("Department: %s\n", assetDepartments[i]);
            printf("Condition: %s\n", assetConditions[i]);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Asset not found.\n");
    }
}

void assetReport(void)
{
    double totalValue = 0;

    if (assetCount == 0)
    {
        printf("\nNo assets available for report.\n");
        return;
    }

    for (int i = 0; i < assetCount; i++)
    {
        totalValue += purchaseValues[i];
    }

    printf("\n--- ASSET REPORT ---\n");
    printf("Total Assets: %d\n", assetCount);
    printf("Total Purchase Value: %.2f\n", totalValue);
}