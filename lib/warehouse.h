#ifndef WAREHOUSE_DOT_H
#define WAREHOUSE_DOT_H

struct item;
void readDataFromFile(struct item *toy, int *nt, char filepath[]);
void saveDataToFile(struct item *toy, int nt, char filepath[]);
void backUpData(struct item *toy, int nt);
void restoreData(struct item *toy, int *nt);
void storeReport(struct item toy[], int n);
void displayAllToys(struct item toy[], int n);
void addNewToy(struct item toy[], int *n);
void removeToy(struct item toy[], int *n);
void updateToyDetails(struct item toy[], int n);
float totalPrice(struct item toy[], int n);
void showCart(struct item cart[], int nc);
void addToCart(struct item toy[], struct item *cart[], int *nt, int *nc);
void removeFromCart(struct item *cart[], int *nc);
void clearCart(struct item *cart[], int *nc);

#endif