#include <stdio.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void displayAllReports(void)
{
    printf("\n========================================\n");
    printf("          MFMS REPORTS\n");
    printf("========================================\n");

    printf("\n1. Employee Report\n");
    employeeReport();

    printf("\n2. Budget Report\n");
    budgetReport();

    printf("\n3. Supplier Report\n");
    supplierReport();

    printf("\n4. Asset Report\n");
    assetReport();

    printf("\n========================================\n");
    printf("        END OF REPORTS\n");
    printf("========================================\n");
}