#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define NAME_LEN      50
#define DEPT_LEN      30
#define DEDUCTION_RATE 0.10


void employeeMenu(void);

void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void displaySalaryInfo(void);


double calculateGrossSalary(double basic, double housing, double transport);
double calculateDeduction(double gross);
double calculateNetSalary(double gross, double deduction);

int    getEmployeeCount(void);
double getAverageSalary(void);
double getHighestSalary(void);
double getLowestSalary(void);

#endif
