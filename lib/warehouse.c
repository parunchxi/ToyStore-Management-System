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

/// Tracking and Reorder Toy
void TrackingAndReorderToy(struct item toy[], int n){

  banner();
  header("Tracking and Reorder Toy");
  
  int reorderThreshold = 10;
  int reorderQuantity = 100;
  int checker = 1;

  for (int i = 0; i < n; i++)
  {
      if(toy[i].quantity <= reorderThreshold)
      {
        char detail[255];
        toy[i].quantity = reorderQuantity;
        sprintf(detail, "%d/%s/%.2f/%d", toy[i].id, toy[i].name, toy[i].price, reorderQuantity);
        saveLog("System", "ReorderToy", "success", detail);
        
        if(checker == 1){
            printf("Low quantity toys!\n");
        }

        
        printf("Reorder %d\t%-20s\t to %d finish.\n", toy[i].id, toy[i].name , toy[i].quantity);
        checker++;
        saveDataToFile(toy, n, "../data/inventory.bin");
      }
  }
    if(checker == 1){
        printf("No low quantity toys.\n");
    }
  printf("\n");
}

void backUpData(char user[], struct item *toy, int nt)
{
    saveDataToFile(toy, nt, "../data/backup.bin");
    saveLog(user, "backup", "success", "");
    banner();
    success("\nDatabase backed up successfully!\n");
    return;
}

void restoreData(char user[], struct item *toy, int *nt)
{
    readDataFromFile(toy, nt, "../data/backup.bin");
    saveDataToFile(toy, *nt, "../data/inventory.bin");
    saveLog(user, "restore", "success", "");
    banner();
    success("\nDatabase restored successfully!\n");
    return;
}

void displayAllToys(struct item toy[], int n)
{
    
    banner();
    TrackingAndReorderToy(toy, n);
    header("All Toys");
    bold("ID\tName\t\t\tPrice\tQuantity");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%-20s\t%.2f\t%d\n", toy[i].id, toy[i].name, toy[i].price, toy[i].quantity);
    }
    printf("\n");
}

void addNewToy(char user[], struct item toy[], int *n)
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
    char detail[255];
    sprintf(detail, "%d/%s/%.2f/%d", toy[*n - 1].id, toy[*n - 1].name, toy[*n - 1].price, toy[*n - 1].quantity);
    saveLog(user, "addNewToy", "success", detail);
    success("\nToy added successfully!\n");
}

void removeToy(char user[], struct item toy[], int *n)
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
            char detail[255];
            sprintf(detail, "%d/%s/%.2f/%d", toy[i].id, toy[i].name, toy[i].price, toy[i].quantity);
            saveLog(user, "removeToy", "success", detail);
            banner();
            success("\nToy removed successfully!\n");
            return;
        }
    }
    danger("Invalid ID!\n");
}

void updateToyDetails(char user[], struct item toy[], int n)
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
            char oldName[255];
            strcpy(oldName, toy[i].name);
            float oldPrice = toy[i].price;
            int oldQuantity = toy[i].quantity;
            printf("Name: ");
            scanf("%s", toy[i].name);
            printf("Price: ");
            scanf("%f", &toy[i].price);
            printf("Quantity: ");
            scanf("%d", &toy[i].quantity);
            char detail[255];
            sprintf(detail, "%d-%s/%.2f/%d-%s/%.2f/%d", toy[i].id, oldName, oldPrice, oldQuantity, toy[i].name, toy[i].price, toy[i].quantity);
            saveLog(user, "updateToyDetails", "success", detail);
            saveDataToFile(toy, n, "../data/inventory.bin");
            banner();
            success("\nToy updated successfully\n");
            return;
        }
    }
    danger("Invalid ID!\n");
}

int totalQuantity(struct item toy[], int n)
{
    int totalQuantity = 0;
    for (int i = 0; i < n; i++)
        totalQuantity += toy[i].quantity;
    return totalQuantity;
}

float totalPrice(struct item toy[], int n)
{
    float totalPrice = 0;
    for (int i = 0; i < n; i++)
        totalPrice += toy[i].price * toy[i].quantity;
    return totalPrice;
}

void showCart(struct item cart[], int nc)
{
    header("Cart");
    if (nc == 0)
    {
        printf("Cart is empty!\n\n");
        return;
    }
    bold("ID\tName\t\t\tPrice\tQuantity");
    for (int i = 0; i < nc; i++)
    {
        printf("%d\t%-20s\t%.2f\t%d\n", cart[i].id, cart[i].name, cart[i].price, cart[i].quantity);
    }
    printf("\nTotal Quantity: %d\n", totalQuantity(cart, nc));
    printf("Total Price: %.2f\n\n", totalPrice(cart, nc));
}

void addToCart(struct item toy[], struct item cart[], int *nt, int *nc)
{
    displayAllToys(toy, *nt);
    showCart(cart, *nc);
    header("Add to Cart");
    int id, quantity;
    printf("ID: ");
    scanf("%d", &id);
    for (int i = 0; i < *nt; i++)
    {
        if (toy[i].id == id)
        {
            for (int j = 0; j < *nc; j++)
            {
                if (cart[j].id == id)
                {
                    printf("Quantity: ");
                    scanf("%d", &quantity);
                    if (cart[j].quantity + quantity > toy[i].quantity)
                    {
                        banner();
                        showCart(cart, *nc);
                        danger("Not enough quantity!\n");
                        return;
                    }
                    else if (quantity <= 0)
                    {
                        banner();
                        showCart(cart, *nc);
                        danger("Invalid quantity!\n");
                        return;
                    }
                    cart[j].quantity += quantity;
                    banner();
                    showCart(cart, *nc);
                    success("Toy added to cart successfully!\n");
                    return;
                }
            }
            printf("Quantity: ");
            scanf("%d", &quantity);
            if (quantity > toy[i].quantity)
            {
                banner();
                showCart(cart, *nc);
                danger("Not enough quantity!\n");
                return;
            }
            else if (quantity <= 0)
            {
                banner();
                showCart(cart, *nc);
                danger("Invalid quantity!\n");
                return;
            }
            cart[*nc].id = toy[i].id;
            strcpy(cart[*nc].name, toy[i].name);
            cart[*nc].price = toy[i].price;
            cart[*nc].quantity = quantity;
            (*nc)++;
            banner();
            showCart(cart, *nc);
            success("Toy added to cart successfully!\n");
            return;
        }
    }
    banner();
    showCart(cart, *nc);
    danger("Invalid ID!\n");
}

void removeFromCart(struct item cart[], int *nc)
{
    banner();
    showCart(cart, *nc);
    header("Remove from Cart");
    int id;
    printf("ID: ");
    scanf("%d", &id);
    for (int i = 0; i < *nc; i++)
    {
        if (cart[i].id == id)
        {
            for (int j = i; j < *nc - 1; j++)
                cart[j] = cart[j + 1];
            (*nc)--;
            banner();
            showCart(cart, *nc);
            success("Toy removed from cart successfully!\n");
            return;
        }
    }
    banner();
    showCart(cart, *nc);
    danger("Invalid ID!\n");
}

void clearCart(struct item cart[], int *nc)
{
    *nc = 0;
    banner();
    success("\nCart cleared successfully!\n");
}







void checkout(char user[], struct item toy[], struct item cart[], int *nt, int *nc)
{
    for (int i = 0; i < *nc; i++)
    {
        for (int j = 0; j < *nt; j++)
        {
            if (cart[i].id == toy[j].id)
            {
                toy[j].quantity -= cart[i].quantity;
                char detail[255];
                sprintf(detail, "%d/%s/%.2f/%d", cart[j].id, cart[j].name, cart[j].price, cart[j].quantity);
                saveLog(user, "checkout", "success", detail);
            }
        }
    }
    clearCart(cart, nc);
    saveDataToFile(toy, *nt, "../data/inventory.bin");
    banner();
    success("\nCheckout successful!\n");
}