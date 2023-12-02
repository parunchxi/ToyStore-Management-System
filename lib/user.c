struct user
{
    char username[255];
    char password[255];
    char role[255];
};

void getUserData(struct user *user, int *i)
{
    FILE *fp = fopen("../data/user.bin", "r");
    char line[255];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        sscanf(line, "%[^,],%[^,],%[^\n]", user[*i].username, user[*i].password, user[*i].role);
        (*i)++;
    }
    fclose(fp);
}

void passwordInput(char *password)
{
    char c;
    int i = 0;
    while (1)
    {
        c = getch();
        if (c == 13)
        {
            // Enter
            printf("\n");
            break;
        }
        else if (c == 8)
        {
            // Backspace
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i] = c;
            i++;
            printf("*");
        }
    }
    password[i] = '\0';
}

int login()
{
    struct user user[100];
    int i = -1;
    getUserData(user, &i);

    char username[255];
    char password[255];

    banner();
    header("Login");
    printf("Username: ");
    scanf("%s", username);
    for (int j = 0; j <= i; j++)
    {
        if (strcmp(username, user[j].username) == 0)
        {
            printf("Password: ");
            passwordInput(password);
            if (strcmp(password, user[j].password) == 0)
            {
                banner();
                success("\nLogin success!\n");
                delay(2000);
                if (strcmp(user[j].role, "admin") == 0)
                {
                    return 1;
                }
                else if (strcmp(user[j].role, "cashier") == 0)
                {
                    return 2;
                }
                else if (strcmp(user[j].role, "god") == 0)
                {
                    return 3;
                }
            }
            else
            {
                danger("Wrong password!");
                return 0;
            }
        }
        else if (j == i)
        {
            danger("Username not found!");
            return 0;
        }
    }
}