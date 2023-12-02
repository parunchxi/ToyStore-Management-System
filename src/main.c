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
        if (choice[0] == 1)
        {
            do
            {
                user = login();
                if (user == 1)
                {
                    // Admin
                }
                else if (user == 2)
                {
                    // Cashier
                }
                else if (user == 0)
                {
                    printf("1. Try again\n");
                    printf("0. Exit\n");
                    printf(">> ");
                    scanf("%d", &choice[1]);
                    if (choice[1] == 0)
                        return 0;
                    else if (choice[1] == 1)
                        continue;
                    else
                    {
                        danger("Invalid choice!");
                        printf("Press enter to continue...");
                        getch();
                    }
                }
            } while (choice[1] != 0);
        }
        else if (choice[0] == 0)
        {
            return 0;
        }
        else
        {
            danger("Invalid choice!");
            printf("Press enter to continue...");
            getch();
        }
    } while (choice[0] != -1);

    return 0;
}
