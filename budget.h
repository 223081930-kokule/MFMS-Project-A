#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20
#define DEPT_NAME_LEN   50

/* Menu and user-facing operations */
void budgetMenu(void);
void addDepartmentBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void displayExceededDepartments(void);
void displayBudgetReport(void);   /* also called by the Reports module */

/* Calculation helpers (parameters in, value out) */
double calculateRemaining(double allocated, double spent);
int    isWithinBudget(double allocated, double spent);

#endif
