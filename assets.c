#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets.h"

static Asset assets[MAX_ASSETS];
static int assetCount = 0;

static void readLine(const char *prompt, char *buf, int size) {
    printf("%s", prompt);
    if (fgets(buf, size, stdin) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
    }
}

void addAsset(void) {
    if (assetCount >= MAX_ASSETS) {
        printf("\nAsset storage is full (%d max).\n", MAX_ASSETS);
        return;
    }

    Asset newAsset;
    char temp[64];
    int duplicate = 0;

    printf("\n========== ADD ASSET ==========\n");

    while (1) {
        printf("Enter Asset ID: ");
        if (fgets(temp, sizeof(temp), stdin) != NULL) {
            newAsset.id = atoi(temp);
            if (newAsset.id > 0) break;
        }
        printf("Invalid ID. Please enter a positive integer.\n");
    }

    for (int i = 0; i < assetCount; i++) {
        if (assets[i].id == newAsset.id) {
            duplicate = 1;
            break;
        }
    }

    if (duplicate) {
        printf("An asset with this ID already exists.\n");
        return;
    }

    readLine("Enter Asset Name: ", newAsset.name, STR_LEN);
    readLine("Enter Asset Type: ", newAsset.type, STR_LEN);

    while (1) {
        printf("Enter Asset Value (N$): ");
        if (fgets(temp, sizeof(temp), stdin) != NULL) {
            newAsset.value = atof(temp);
            if (newAsset.value >= 0) break;
        }
        printf("Invalid value. Amount cannot be negative.\n");
    }

    readLine("Enter Department: ", newAsset.department, STR_LEN);
    readLine("Enter Condition (e.g., Good, Fair, Poor): ", newAsset.condition, STR_LEN);

    assets[assetCount] = newAsset;
    assetCount++;

    printf("\nAsset added successfully!\n");
}

void displayAssets(void) {
    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    printf("\n================================ ASSET LIST ================================\n");
    printf("%-5s %-18s %-12s %-13s %-14s %-10s\n", "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < assetCount; i++) {
        printf("%-5d %-18s %-12s %-13.2f %-14s %-10s\n",
            assets[i].id,
            assets[i].name,
            assets[i].type,
            assets[i].value,
            assets[i].department,
            assets[i].condition
        );
    }
    printf("----------------------------------------------------------------------------\n");
    printf("Total Assets: %d\n", assetCount);
}

void searchAsset(void) {
    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    int searchId;
    printf("\n========== SEARCH ASSET ==========\n");
    printf("Enter Asset ID to search: ");
    scanf("%d", &searchId);
    getchar();

    int found = 0;
    for (int i = 0; i < assetCount; i++) {
        if (assets[i].id == searchId) {
            printf("\nAsset Found!\n");
            printf("ID        : %d\n", assets[i].id);
            printf("Name      : %s\n", assets[i].name);
            printf("Type      : %s\n", assets[i].type);
            printf("Value     : N$%.2f\n", assets[i].value);
            printf("Department: %s\n", assets[i].department);
            printf("Condition : %s\n", assets[i].condition);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo asset found with ID %d.\n", searchId);
    }
}

void assetMenu(void) {
    char buf[16];
    int choice;

    do {
        printf("\n========== ASSET MANAGEMENT ==========\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            choice = atoi(buf);
        } else {
            choice = 4;
        }

        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Enter a number from 1 to 4.\n");
        }
    } while (choice != 4);
}

int getAssetCount(void) {
    return assetCount;
}

void getAssetIds(int ids[]) {
    for (int i = 0; i < assetCount; i++) {
        ids[i] = assets[i].id;
    }
}

void getAssetNames(char names[][STR_LEN]) {
    for (int i = 0; i < assetCount; i++) {
        strcpy(names[i], assets[i].name);
    }
}

void getAssetTypes(char types[][STR_LEN]) {
    for (int i = 0; i < assetCount; i++) {
        strcpy(types[i], assets[i].type);
    }
}

void getAssetValues(double values[]) {
    for (int i = 0; i < assetCount; i++) {
        values[i] = assets[i].value;
    }
}

void getAssetDepts(char depts[][STR_LEN]) {
    for (int i = 0; i < assetCount; i++) {
        strcpy(depts[i], assets[i].department);
    }
}

void getAssetConditions(char conditions[][STR_LEN]) {
    for (int i = 0; i < assetCount; i++) {
        strcpy(conditions[i], assets[i].condition);
    }
}