

void batman_loading()
{
    int i, j;

    for (i = 0; i < 10; i++)
    {
        printf("\033[H\033[J");

        if (i >= 0)
        {
            printf("\033[0;95m");
        }
        printf("       _.    _   _    ._\n");
        if (i >= 0)
        {
            printf("\033[0m");
        }

        if (i >= 1)
        {
            printf("\033[0;95m");
        }
        printf("  .o888P     Y8o8Y     Y888o.\n");
        if (i >= 1)
        {
            printf("\033[0m");
        }

        if (i >= 2)
        {
            printf("\033[0;95m");
        }
        printf(" d88888      88888      88888b\n");
        if (i >= 2)
        {
            printf("\033[0m");
        }

        if (i >= 3)
        {
            printf("\033[0;95m");
        }
        printf("d888888b_  _d88888b_  _d888888b\n");
        if (i >= 3)
        {
            printf("\033[0m");
        }

        if (i >= 4)
        {
            printf("\033[0;95m");
        }
        printf("8888888888\e[0m TOY STORE \033[0m");

        if (i >= 4)
        {
            printf("\033[0;95m");
        }
        printf("8888888888\n");

        if (i >= 4)
        {
            printf("\033[0m");
        }

        if (i >= 5)
        {
            printf("\033[0;95m");
        }
        printf("888888\e[0m MANAGEMENT SYSTEM \033[0m");

        if (i >= 5)
        {
            printf("\033[0;95m");
        }

        printf("888888\n");
        if (i >= 5)
        {
            printf("\033[0m");
        }

        if (i >= 6)
        {
            printf("\033[0;95m");
        }
        printf("Y8888Y8Y888Y8Y888Y8Y888Y8Y8888Y\n");
        if (i >= 6)
        {
            printf("\033[0m");
        }

        if (i >= 7)
        {
            printf("\033[0;95m");
        }
        printf(" Y888   'V'   Y8P   'V'   888Y\n");
        if (i >= 7)
        {
            printf("\033[0m");
        }

        if (i >= 8)
        {
            printf("\033[0;95m");
        }
        printf("  '8o          V          o8'\n");
        if (i >= 8)
        {
            printf("\033[0m");
        }

        if (i >= 9)
        {
            printf("\033[0;95m");
        }
        printf("    '                     '\n");
        if (i >= 9)
        {
            printf("\033[0m");
        }

        delay(300);
    }
}