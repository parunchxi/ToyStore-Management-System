void clearScreen()
{
    system("cls");
}

void resetStyle()
{
    printf("\e[0m");
}

void banner()
{
    clearScreen();
    printf("\e[105m   TOY STORE MANAGEMENT SYSTEM   \e[0m\n");
}

void danger(char *msg)
{
    printf("\e[0;31m%s\n", msg);
    resetStyle();
}

void success(char *msg)
{
    printf("\e[0;32m%s\n", msg);
    resetStyle();
}

void header(char *msg)
{
    printf("\e[1;95m%s\n", msg);
    resetStyle();
}
