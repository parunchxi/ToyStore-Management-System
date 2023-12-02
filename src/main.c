#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "../lib/user.c"
#include "../lib/decoration.c"
#include "../lib/warehouse.c"

void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds)
        ;
}

int main()
{
    struct item toy[100];
    int nt;
    readDataFromFile(toy, &nt, "../data/inventory.bin");

    int user = 0;
    int choice[5] = {-1, -1, -1, -1, -1};

    do
    {
        banner();
        printf("1. Login\n");
        printf("0. Exit\n");
        printf(">> ");
        scanf("%d", &choice[0]);
        switch (choice[0])
        {
        case 1:
            do
            {
                user = login();
                switch (user)
                {
                case 1:
                    // Admin
                    banner();
                    do
                    {
                        header("Admin Menu");
                        printf("1. View Store Report\n");
                        printf("2. Display All Toys\n");
                        printf("3. Add a New Toy\n");
                        printf("4. Remove a Toy\n");
                        printf("5. Update Toy Details\n");
                        printf("6. Back Up Database\n");
                        printf("7. Restore Database\n");
                        printf("0. Logout\n");
                        printf(">> ");
                        scanf("%d", &choice[1]);
                        switch (choice[1])
                        {
                        case 1:
                            // View Store Report
                            break;
                        case 2:
                            // Display All Toys
                            displayAllToys(toy, nt);
                            break;
                        case 3:
                            // Add a New Toy
                            addNewToy(toy, &nt);
                            break;
                        case 4:
                            // Remove a Toy
                            removeToy(toy, &nt);
                            break;
                        case 5:
                            // Update Toy Details
                            updateToyDetails(toy, nt);
                            break;
                        case 6:
                            // Back Up Database
                            backUpData(toy, nt);
                            break;
                        case 7:
                            // Restore Database
                            restoreData(toy, &nt);
                            readDataFromFile(toy, &nt, "../data/inventory.bin");
                            break;
                        case 0:
                            danger("Logging out...");
                            delay(1000);
                            break;
                        default:
                            danger("Invalid choice!");
                            printf("Press enter to continue...\n");
                            getch();
                        }
                    } while (choice[1] != 0);
                case 2:
                    // Cashier
                    break;
                case 0:
                    printf("1. Try again\n");
                    printf("0. Exit\n");
                    printf(">> ");
                    scanf("%d", &choice[0]);
                    switch (choice[0])
                    {
                    case 1:
                        continue;
                    case 0:
                        danger("Exiting...");
                        delay(1000);
                        return 0;
                    default:
                        danger("Invalid choice!");
                        printf("Press enter to continue...\n");
                        getch();
                    }
                }
            } while (choice[0] != 0);
        case 0:
            danger("Exiting...");
            delay(1000);
            return 0;
        default:
            danger("Invalid choice!");
            printf("Press enter to continue...\n");
            getch();
        }
    } while (choice[0] != 0);

    return 0;
}
