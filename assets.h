#ifndef ASSETS_H
#define ASSETS_H

// Asset Management Structure
typedef struct {
    int assetID;
    char assetName[50];
    char category[30];
    float value;
    char purchaseDate[15];
} Asset;

// Function Prototypes
void addAsset();
void viewAssets();
void updateAsset();
void deleteAsset();

#endif