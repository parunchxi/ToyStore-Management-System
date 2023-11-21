#include <stdio.h>
#include <string.h>

struct item
{
    int id;
    char name[255];
    float price;
    int quantity;
};

void readDataFromFile(struct item *toy, int *nt, char filepath[])
{
    FILE *databaseFile = fopen(filepath, "r");
    if (databaseFile == NULL)
    {
        fclose(databaseFile);
        FILE *databaseFile = fopen(filepath, "w");
        fclose(databaseFile);
        return;
    }
    char line[255];
    *nt = -1;
    while (fgets(line, sizeof(line), databaseFile) != NULL)
    {
        sscanf(line, "%d,%[^,],%f,%d", &toy[*nt].id, toy[*nt].name, &toy[*nt].price, &toy[*nt].quantity);
        (*nt)++;
    }
    fclose(databaseFile);
    return;
}

void saveDataToFile(struct item *toy, int nt, char filepath[])
{
    FILE *databaseFile = fopen(filepath, "w");
    if (databaseFile == NULL)
    {
        perror("File could not be opened");
        return;
    }
    fprintf(databaseFile, "ID,Name,Price,Quantity\n");
    for (int i = 0; i < nt; i++)
    {
        fprintf(databaseFile, "%d,%s,%.2f,%d\n", toy[i].id, toy[i].name, toy[i].price, toy[i].quantity);
    }
    fclose(databaseFile);
    readDataFromFile(toy, &nt, "../data/inventory.bin");
    return;
}

void backUpData(struct item *toy, int nt)
{
    saveDataToFile(toy, nt, "../data/backup.bin");
    return;
}

void restoreData(struct item *toy, int *nt)
{
    // โค้ดด้านล่างมัน warning แต่ก็ทำงานได้
    // readDataFromFile(toy, &nt, "backup.bin");
    // saveDataToFile(toy, nt, "inventory.bin");
    return;
}

void storeReport(struct item toy[], int n)
{
    // code
}

void addNewToy(struct item toy[], int *n)
{
    printf("\nEnter details for the new toy:\n");
    printf("ID: ");
    scanf("%d", &toy[*n].id);
    for (int i = 0; i < *n; i++)
    {
        if (toy[i].id == toy[*n].id)
        {
            printf("\nID already exists. Please enter a different ID.\n");
            return;
        }
    }
    printf("Name: ");
    scanf("%s", toy[*n].name);
    printf("Price: ");
    scanf("%f", &toy[*n].price);
    printf("Quantity: ");
    scanf("%d", &toy[*n].quantity);
    (*n)++;
    saveDataToFile(toy, *n, "../data/inventory.bin");
    printf("\nToy added successfully\n");
}

void removeToy(struct item toy[], int *n)
{
    printf("\nRemoving a toy\n");
    int id;
    printf("Enter the ID of the toy to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < *n; i++)
    {
        if (toy[i].id == id)
        {
            for (int j = i; j < *n - 1; j++)
            {
                toy[j] = toy[j + 1];
            }
            (*n)--;
            saveDataToFile(toy, *n, "../data/inventory.bin");
            printf("\nToy removed successfully\n");
            return;
        }
    }
    printf("Toy not found\n");
}

void updateToyDetails(struct item toy[], int n)
{
    printf("\nUpdating a toy\n");
    int id;
    printf("Enter the ID of the toy to update: ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++)
    {
        if (toy[i].id == id)
        {
            printf("Name: ");
            scanf("%s", toy[i].name);
            printf("Price: ");
            scanf("%f", &toy[i].price);
            printf("Quantity: ");
            scanf("%d", &toy[i].quantity);
            saveDataToFile(toy, n, "../data/inventory.bin");
            printf("\nToy updated successfully\n");
            return;
        }
    }
    printf("\nToy not found!\n");
}

void searchToys(struct item toy[], int n)
{
    printf("\nSearching for toys\n");
    char name[255];
    printf("Enter the name of the toy to search for: ");
    scanf("%s", name);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(toy[i].name, name) == 0)
        {
            printf("ID\tName\t\t\tPrice\tQuantity\n");
            printf("%d\t%-20s\t%.2f\t%d\n", toy[i].id, toy[i].name, toy[i].price, toy[i].quantity);
            return;
        }
    }
    printf("\nToy not found!\n");
}

void sellToy(struct item toy[], int *n)
{
    // code
}

void displayAllToys(struct item toy[], int n)
{
    printf("\nAll Toys\n");
    printf("ID\tName\t\t\tPrice\tQuantity\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%-20s\t%.2f\t%d\n", toy[i].id, toy[i].name, toy[i].price, toy[i].quantity);
    }
}

int main()
{
    // Intialize data from file
    struct item toy[100];
    int nt;
    readDataFromFile(toy, &nt, "../data/inventory.bin");

    int user, select;
    do
    {
        printf("\nToy Store Management System\n");
        printf("1. Owner\n");
        printf("2. Cashier\n");
        printf("0. Exit\n");
        printf("Select user: ");
        scanf("%d", &user);

        switch (user)
        {

        case 1:
            do
            {
                printf("\nOwner Menu\n");
                printf("1. View Store Report\n");
                printf("2. Display All Toys\n");
                printf("3. Add a New Toy\n");
                printf("4. Remove a Toy\n");
                printf("5. Update Toy Details\n");
                printf("6. Search for Toys\n");
                printf("7. Back Up Database\n");
                printf("8. Restore Database\n");
                printf("0. Back to User Selection\n");
                printf("Enter your choice: ");
                scanf("%d", &select);

                switch (select)
                {
                case 1:
                    storeReport(toy, nt);
                    break;
                case 2:
                    displayAllToys(toy, nt);
                    break;
                case 3:
                    addNewToy(toy, &nt);
                    break;
                case 4:
                    removeToy(toy, &nt);
                    break;
                case 5:
                    updateToyDetails(toy, nt);
                    break;
                case 6:
                    searchToys(toy, nt);
                    break;
                case 7:
                    backUpData(toy, nt);
                    break;
                case 8:
                    restoreData(toy, &nt);
                    break;
                case 0:
                    printf("\nReturning to User Selection...\n");
                    break;
                default:
                    printf("\nInvalid choice. Please enter a valid option.\n");
                }
            } while (select != 0);
            break;
        case 2:
            printf("\nCashier Menu\n");
            sellToy(toy, &nt);
            break;
        case 0:
            printf("\nExiting the program.\n\n");
            break;
        default:
            printf("\nInvalid choice! Please enter a valid option.\n");
        }
    } while (user != 0);

    return 0;
}