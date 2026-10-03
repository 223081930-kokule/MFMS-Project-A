/* reports.h - Reports module (Student 5)
 * Municipal Financial Management System (MFMS) - PAP521S Project A
 *
 * Every report receives the data it needs as parameters (arrays + count),
 * so this module does not depend on how the other modules store their data.
 * All string arrays share the same column width STR_LEN - the whole group
 * must use the same value (ideally defined once in a shared header).
 */
#ifndef REPORTS_H
#define REPORTS_H

#ifndef STR_LEN
#define STR_LEN 50
#endif

/* Individual reports */
void employeeReport(char names[][STR_LEN], char depts[][STR_LEN],
                    double salaries[], int count);

void budgetReport(char depts[][STR_LEN], double allocated[],
                  double spent[], int count);

void supplierReport(int ids[], char names[][STR_LEN], char emails[][STR_LEN],
                    char phones[][STR_LEN], char towns[][STR_LEN], int count);

void assetReport(int ids[], char names[][STR_LEN], char types[][STR_LEN],
                 double values[], char depts[][STR_LEN],
                 char conditions[][STR_LEN], int count);

/* Reports sub-menu (called from main menu option 5) */
void displayReports(
    char empNames[][STR_LEN], char empDepts[][STR_LEN],
    double empSalaries[], int empCount,
    char budDepts[][STR_LEN], double budAllocated[], double budSpent[],
    int budCount,
    int supIds[], char supNames[][STR_LEN], char supEmails[][STR_LEN],
    char supPhones[][STR_LEN], char supTowns[][STR_LEN], int supCount,
    int assetIds[], char assetNames[][STR_LEN], char assetTypes[][STR_LEN],
    double assetValues[], char assetDepts[][STR_LEN],
    char assetConds[][STR_LEN], int assetCount);

#endif
