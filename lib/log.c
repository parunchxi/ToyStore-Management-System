void saveLog(char user[], char action[], char status[], char detail[])
{
    FILE *logFile = fopen("../data/log.bin", "a");
    if (logFile == NULL)
    {
        perror("File could not be opened");
        return;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(logFile, "%d-%02d-%02d,%02d:%02d:%02d,%s,%s,%s,%s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, user, action, status, detail);
    fclose(logFile);
    return;
}

void showLogByDate(char date[])
{
    FILE *logFile = fopen("../data/log.bin", "r");
    if (logFile == NULL)
    {
        perror("File could not be opened");
        return;
    }
    char line[255];
    char *token;
    char *dateToken;
    char *timeToken;
    char *userToken;
    char *actionToken;
    char *statusToken;
    char *detailToken;
    int logsFound = 0;
    bold("Time\t\tUser\t\tStatus\t\tAction\t\tDetail");
    while (fgets(line, sizeof(line), logFile) != NULL)
    {
        if (strcmp(line, "\n") == 0)
            continue;
        token = strtok(line, ",");
        dateToken = token;
        token = strtok(NULL, ",");
        timeToken = token;
        token = strtok(NULL, ",");
        userToken = token;
        token = strtok(NULL, ",");
        actionToken = token;
        token = strtok(NULL, ",");
        statusToken = token;
        token = strtok(NULL, ",");
        detailToken = token;

        if (strcmp(date, "today") == 0)
        {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char today[255];
            sprintf(today, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
            if (strcmp(dateToken, today) == 0)
            {
                printf("%s\t%s\t\t%s\t\t%s\t\t%s", timeToken, userToken, statusToken, actionToken, detailToken);
                logsFound = 1;
            }
        }
        else
        {
            if (strcmp(dateToken, date) == 0)
            {
                printf("%s\t%s\t\t%s\t\t%s\t\t%s", timeToken, userToken, statusToken, actionToken, detailToken);
                logsFound = 1;
            }
        }
    }

    if (!logsFound)
    {
        printf("No logs found for the specified date.\n");
    }
    printf("\n");
    fclose(logFile);
}