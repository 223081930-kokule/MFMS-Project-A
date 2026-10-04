#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

#ifndef STR_LEN
#define STR_LEN 50
#endif

typedef struct {
    int id;
    char name[STR_LEN];
    char type[STR_LEN];
    double value;
    char department[STR_LEN];
    char condition[STR_LEN];
} Asset;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);

int getAssetCount(void);
void getAssetIds(int ids[]);
void getAssetNames(char names[][STR_LEN]);
void getAssetTypes(char types[][STR_LEN]);
void getAssetValues(double values[]);
void getAssetDepts(char depts[][STR_LEN]);
void getAssetConditions(char conditions[][STR_LEN]);

#endif