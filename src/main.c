#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "../lib/decoration.c"
#include "../lib/log.c"
#include "../lib/reusable.c"
#include "../lib/user.c"
#include "../lib/warehouse.c"
#include "../lib/bat.c"

int main()
{
    struct item toy[100];
    int nt;
    readDataFromFile(toy, &nt, "../data/inventory.bin");
    int loginChoice;
    do
    {
        batman_loading();
        banner();
        printf("1. Login\n");
        printf("0. Exit\n");
        printf(">> ");
        scanf("%d", &loginChoice);
        switch (loginChoice)
        {
        case 1:
            do
            {
                char username[100];
                int role = login(username);
                switch (role)
                {
                case 1:
                    // Admin
                    int adminChoice;
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
                        printf("8. Add New User\n");
                        printf("9. Remove User\n");
                        printf("0. Logout\n");
                        printf(">> ");
                        scanf("%d", &adminChoice);
                        switch (adminChoice)
                        {
                        case 1:
                            // View Store Report
                            banner();
                            header("Store Report");
                            char date[255];
                            printf("Date (YYYY-MM-DD): ");
                            scanf("%s", date);
                            showLogByDate(date);
                            break;
                        case 2:
                            // Display All Toys
                            displayAllToys(toy, nt);
                            break;
                        case 3:
                            // Add a New Toy
                            addNewToy(username, toy, &nt);
                            break;
                        case 4:
                            // Remove a Toy
                            removeToy(username, toy, &nt);
                            break;
                        case 5:
                            // Update Toy Details
                            updateToyDetails(username, toy, nt);
                            break;
                        case 6:
                            // Back Up Database
                            backUpData(username, toy, nt);
                            break;
                        case 7:
                            // Restore Database
                            restoreData(username, toy, &nt);
                            readDataFromFile(toy, &nt, "../data/inventory.bin");
                            break;
                        case 8:
                            // Add New User
                            addNewUser(username);
                            break;
                        case 9:
                            // Remove User
                            removeUser(username);
                            break;
                        case 0:
                            saveLog(username, "logout", "success", "");
                            danger("Logging out...");
                            delay(1000);
                            break;
                        default:
                            danger("Invalid choice!");
                            printf("Press enter to continue...\n");
                            getch();
                        }
                    } while (adminChoice != 0);
                    break;
                case 2:
                    // Cashier
                    int cashierChoice;
                    struct item cart[100];
                    int nc = 0;
                    banner();
                    do
                    {
                        header("Cashier Menu");
                        printf("1. Display All Toys\n");
                        printf("2. Add to Cart\n");
                        printf("3. Remove from Cart\n");
                        printf("4. Clear cart\n");
                        printf("5. Checkout\n");
                        printf("0. Logout\n");
                        printf(">> ");
                        scanf("%d", &cashierChoice);
                        switch (cashierChoice)
                        {
                        case 1:
                            // Display All Toys
                            displayAllToys(toy, nt);
                            showCart(cart, nc);
                            break;
                        case 2:
                            // Add to Cart
                            addToCart(toy, cart, &nt, &nc);
                            break;
                        case 3:
                            // Remove from Cart
                            removeFromCart(cart, &nc);
                            break;
                        case 4:
                            // Clear cart
                            int clearCartChoice;
                            banner();
                            showCart(cart, nc);
                            header("Clear Cart");
                            printf("1. Confirm\n");
                            printf("0. Cancel\n");
                            printf(">> ");
                            scanf("%d", &clearCartChoice);
                            switch (clearCartChoice)
                            {
                            case 1:
                                clearCart(cart, &nc);
                                banner();
                                success("\nCart cleared successfully!\n");
                                break;
                            case 0:
                                banner();
                                showCart(cart, nc);
                                warning("Cart not cleared!\n");
                                break;
                            default:
                                danger("Invalid choice!");
                                printf("Press enter to continue...\n\n");
                                getch();
                            }
                        case 5:
                            // Checkout
                            int checkoutChoice;
                            banner();
                            showCart(cart, nc);
                            header("Checkout");
                            printf("1. Confirm\n");
                            printf("0. Cancel\n");
                            printf(">> ");
                            scanf("%d", &checkoutChoice);
                            switch (checkoutChoice)
                            {
                            case 1:
                                checkout(username, toy, cart, &nt, &nc);
                                break;
                            case 0:
                                banner();
                                showCart(cart, nc);
                                warning("Checkout cancelled!\n");
                                break;
                            default:
                                danger("Invalid choice!");
                                printf("Press enter to continue...\n\n");
                                getch();
                            }
                            break;
                        case 0:
                            saveLog(username, "logout", "success", "");
                            danger("Logging out...");
                            delay(1000);
                            break;
                        default:
                            danger("Invalid choice!");
                            printf("Press enter to continue...\n\n");
                            getch();
                        }
                    } while (cashierChoice != 0);
                    break;
                case 0:
                    printf("1. Try again\n");
                    printf("0. Exit\n");
                    printf(">> ");
                    scanf("%d", &loginChoice);
                    switch (loginChoice)
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
            } while (loginChoice != 0);
            break;
        case 0:
            danger("Exiting...");
            delay(1000);
            return 0;
        default:
            danger("Invalid choice!");
            printf("Press enter to continue...\n");
            getch();
        }
    } while (loginChoice != 0);

    return 0;
}
