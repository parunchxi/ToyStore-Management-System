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
    banner();
    success("\nDatabase backed up successfully!\n");
    return;
}

void restoreData(struct item *toy, int *nt)
{
    readDataFromFile(toy, &nt, "../data/backup.bin");
    saveDataToFile(toy, nt, "../data/inventory.bin");
    banner();
    success("\nDatabase restored successfully!\n");
    return;
}

void storeReport(struct item toy[], int n)
{
    // code
}

void displayAllToys(struct item toy[], int n)
{
    banner();
    header("All Toys");
    bold("ID\tName\t\t\tPrice\tQuantity");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%-20s\t%.2f\t%d\n", toy[i].id, toy[i].name, toy[i].price, toy[i].quantity);
    }
    printf("\n");
}

void addNewToy(struct item toy[], int *n)
{
    displayAllToys(toy, *n);
    header("Add a New Toy");
    printf("ID: ");
    scanf("%d", &toy[*n].id);
    for (int i = 0; i < *n; i++)
    {
        if (toy[i].id == toy[*n].id)
        {
            danger("ID already exists. Please enter a different ID.\n");
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
    banner();
    success("\nToy added successfully!\n");
}

void removeToy(struct item toy[], int *n)
{
    displayAllToys(toy, *n);
    header("Remove a Toy");
    int id;
    printf("ID: ");
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
            banner();
            success("\nToy removed successfully!\n");
            return;
        }
    }
    danger("Invalid ID!\n");
}

void updateToyDetails(struct item toy[], int n)
{
    displayAllToys(toy, n);
    header("Update Toy Details");
    int id;
    printf("ID: ");
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
            banner();
            success("\nToy updated successfully\n");
            return;
        }
    }
    danger("Invalid ID!\n");
}

void sellToy(struct item toy[], int *n)
{
    // code
}