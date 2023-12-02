#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "../lib/user.c"
#include "../lib/decoration.c"

void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds)
        ;
}

int main()
{
    int user = 0;
    int choice[10] = {-1};
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
                    break;
                case 2:
                    // Cashier
                    break;
                case 0:
                    printf("1. Try again\n");
                    printf("0. Exit\n");
                    printf(">> ");
                    scanf("%d", &choice[1]);
                    switch (choice[1])
                    {
                    case 1:
                        continue;
                    case 0:
                        return 0;
                    default:
                        danger("Invalid choice!");
                        printf("Press enter to continue...");
                        getch();
                    }
                }
            } while (choice[1] != 0);
        case 0:
            return 0;
        default:
            danger("Invalid choice!");
            printf("Press enter to continue...");
            getch();
        }
    } while (choice[0] != -1);

    return 0;
}
