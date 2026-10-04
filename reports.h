#ifndef REPORTS_H
#define REPORTS_H

#include "suppliers.h"

void reportEmployee(void);
void reportBudget(void);
void reportSupplier(Supplier suppliers[], int supplierCount);
void assetReport(void);
void reportAsset(void);
void displayReports(Supplier suppliers[], int supplierCount);

#endif