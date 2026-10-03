#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    int id;
    char name[50];
    char email[60];
    char telephone[20];
    char town[50];
} Supplier;

void addSupplier(Supplier suppliers[], int *supplierCount);
void displaySuppliers(Supplier suppliers[], int supplierCount);
void searchSupplier(Supplier suppliers[], int supplierCount);

#endif
