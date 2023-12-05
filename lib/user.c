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

void encrypt(char *password, int key)
{
    for (int i = 0; i < strlen(password); i++)
        if (i % 2 == 0)
            password[i] += key;
        else if (i % 3 == 0)
            password[i] -= key;
        else if (i % 5 == 0)
            password[i] += (key - 3);
        else if (i % 7 == 0)
            password[i] -= (key + 4);
        else
            password[i] *= key;
}

int login(char *cuser)
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
            encrypt(password, 4);
            if (strcmp(password, user[j].password) == 0)
            {
                strcpy(cuser, user[j].username);
                saveLog(username, "login", "success", "");
                banner();
                success("\nLogin success!\n");
                delay(1000);
                if (strcmp(user[j].role, "admin") == 0)
                    return 1;
                else if (strcmp(user[j].role, "cashier") == 0)
                    return 2;
                else if (strcmp(user[j].role, "god") == 0)
                    return 3;
            }
            else
            {
                saveLog(username, "login", "failed", "Wrong password!");
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

void showUser()
{
    struct user user[100];
    int i = -1;
    getUserData(user, &i);

    banner();
    header("User List");
    bold("Username\tRole");
    for (int j = 0; j <= i; j++)
    {
        printf("%s\t\t%s\n", user[j].username, user[j].role);
    }
}

void addNewUser(char cuser[100])
{
    struct user user[100];
    int i = -1;
    getUserData(user, &i);

    char username[255];
    char password[255];
    char confirm[255];
    char role[255];

    showUser();
    header("Add User");
    printf("Username: ");
    scanf("%s", username);
    for (int j = 0; j <= i; j++)
    {
        if (strcmp(username, user[j].username) == 0)
        {
            banner();
            danger("\nUsername already exists!\n");
            return;
        }
    }
    printf("Password: ");
    passwordInput(password);
    printf("Confirm Password: ");
    passwordInput(confirm);
    if (strcmp(password, confirm) != 0)
    {
        banner();
        danger("\nPassword doesn't match!\n");
        return;
    }
    printf("Select Role {admin, cashier}\n");
    printf("Role: ");
    scanf("%s", role);
    if (strcmp(role, "admin") != 0 && strcmp(role, "cashier") != 0 && strcmp(role, "god") != 0)
    {
        banner();
        danger("\nRole doesn't exist!\n");
        return;
    }
    encrypt(password, 4);
    FILE *fp = fopen("../data/user.bin", "a");
    fprintf(fp, "%s,%s,%s\n", username, password, role);
    fclose(fp);
    char detail[255];
    sprintf(detail, "%s/%s", username, role);
    saveLog(cuser, "addUser", "success", detail);
    banner();
    success("\nUser added successfully!\n");

    getUserData(user, &i);
}

void removeUser(char cuser[100])
{
    struct user user[100];
    int i = -1;
    getUserData(user, &i);

    char username[255];
    showUser();
    header("Remove User");
    printf("Username: ");
    scanf("%s", username);
    int j;
    for (j = 0; j <= i; j++)
    {
        if (strcmp(username, user[j].username) == 0)
            break;
    }
    if (j > i)
    {
        banner();
        danger("\nUsername not found!\n");
        return;
    }
    FILE *fp = fopen("../data/user.bin", "w");
    fprintf(fp, "Username,Password,Role\n");
    for (int k = 0; k < i; k++)
    {
        if (k != j)
        {
            fprintf(fp, "%s,%s,%s\n", user[k].username, user[k].password, user[k].role);
        }
    }
    fclose(fp);
    char detail[255];
    sprintf(detail, "%s/%s", user[j].username, user[j].role);
    saveLog(cuser, "removeUser", "success", detail);
    banner();
    success("\nUser removed successfully!\n");

    getUserData(user, &i);
}